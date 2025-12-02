#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 8080
#define MAX_CLIENTS 100
#define BUFFER_SIZE 1024

int clients[MAX_CLIENTS];
int client_count = 0;
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

// Function to add client to list
void add_client(int client_socket) {
    pthread_mutex_lock(&clients_mutex);
    clients[client_count++] = client_socket;
    pthread_mutex_unlock(&clients_mutex);
}

// Function to remove client from list
void remove_client(int client_socket) {
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < client_count; i++) {
        if (clients[i] == client_socket) {
            for (int j = i; j < client_count - 1; j++) {
                clients[j] = clients[j + 1];
            }
            break;
        }
    }
    client_count--;
    pthread_mutex_unlock(&clients_mutex);
}

// Function to broadcast message to all clients
void broadcast_message(char *message, int sender_socket) {
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < client_count; i++) {
        if (clients[i] != sender_socket) {
            send(clients[i], message, strlen(message), 0);
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

// Function to get current timestamp
void get_timestamp(char *buffer) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buffer, 64, "[%Y-%m-%d %H:%M:%S]", t);
}

// Function to log messages to log.txt
void log_message(char *message) {
    FILE *fp = fopen("log.txt", "a");
    if (fp != NULL) {
        char timestamp[64];
        get_timestamp(timestamp);
        fprintf(fp, "%s %s\n", timestamp, message);
        fclose(fp);
    }
}

// Thread function to handle each client
void *client_handler(void *arg) {
    int client_socket = *(int *)arg;
    char buffer[BUFFER_SIZE];
    int bytes_received;

    while ((bytes_received = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
        buffer[bytes_received] = '\0';

        // Log the message
        log_message(buffer);

        // Broadcast the message to all other clients
        broadcast_message(buffer, client_socket);
    }

    // Remove client when disconnected
    remove_client(client_socket);
    close(client_socket);
    pthread_exit(NULL);
}

int main() {
    int sockfd, newfd;
    struct sockaddr_in server, client;
    socklen_t c = sizeof(struct sockaddr_in);
    pthread_t thread_id;

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    // Bind
    if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Listen
    if (listen(sockfd, 10) < 0) {
        perror("Listen failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Chat server started on port %d\n", PORT);

    while ((newfd = accept(sockfd, (struct sockaddr *)&client, &c))) {
        printf("Accepted connection from %s:%d\n",
               inet_ntoa(client.sin_addr), ntohs(client.sin_port));

        add_client(newfd);

        if (pthread_create(&thread_id, NULL, client_handler, (void *)&newfd) < 0) {
            perror("Thread creation failed");
            return 1;
        }

        pthread_detach(thread_id);  // Detach thread to handle cleanup automatically
    }

    if (newfd < 0) {
        perror("Accept failed");
        return 1;
    }

    close(sockfd);
    return 0;
}
