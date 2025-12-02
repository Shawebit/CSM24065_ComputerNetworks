#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int sockfd;

void *receive_handler(void *arg) {
    char buffer[BUFFER_SIZE];
    int bytes_received;

    while ((bytes_received = recv(sockfd, buffer, sizeof(buffer), 0)) > 0) {
        buffer[bytes_received] = '\0';
        printf("%s\n", buffer);
    }

    return NULL;
}

int main() {
    struct sockaddr_in server;
    char message[BUFFER_SIZE];
    pthread_t recv_thread;

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr("10.0.0.1");  // Change to server IP if needed

    // Connect
    if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Connect failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to chat server\n");

    // Start thread to receive messages
    pthread_create(&recv_thread, NULL, receive_handler, NULL);

    // Send messages
    while (1) {
        fgets(message, BUFFER_SIZE, stdin);
        send(sockfd, message, strlen(message), 0);
    }

    close(sockfd);
    return 0;
}
