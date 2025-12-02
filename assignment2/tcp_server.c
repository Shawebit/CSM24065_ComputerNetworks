#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <arpa/inet.h>

#define MAX_FRUITS 100
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 100

typedef struct {
    char name[50];
    int quantity;
    time_t last_sold;
} Fruit;

typedef struct {
    char ip[20];
    int port;
} ClientInfo;

Fruit fruits[MAX_FRUITS];
int fruit_count = 0;
ClientInfo clients[MAX_CLIENTS];
int client_count = 0;

void initialize_fruits() {
    strcpy(fruits[0].name, "apple");
    fruits[0].quantity = 50;
    fruits[0].last_sold = 0;
    
    strcpy(fruits[1].name, "banana");
    fruits[1].quantity = 30;
    fruits[1].last_sold = 0;
    
    strcpy(fruits[2].name, "orange");
    fruits[2].quantity = 25;
    fruits[2].last_sold = 0;
    
    fruit_count = 3;
}

int find_fruit(char* name) {
    for (int i = 0; i < fruit_count; i++) {
        if (strcmp(fruits[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

int is_client_exists(char* ip, int port) {
    for (int i = 0; i < client_count; i++) {
        if (strcmp(clients[i].ip, ip) == 0 && clients[i].port == port) {
            return 1;
        }
    }
    return 0;
}

void add_client(char* ip, int port) {
    if (!is_client_exists(ip, port) && client_count < MAX_CLIENTS) {
        strcpy(clients[client_count].ip, ip);
        clients[client_count].port = port;
        client_count++;
    }
}

void display_clients() {
    printf("Clients who have done transactions:\n");
    for (int i = 0; i < client_count; i++) {
        printf("Client %d: %s:%d\n", i+1, clients[i].ip, clients[i].port);
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    
    initialize_fruits();
    
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);
    
    printf("Server listening on port 8080\n");
    
    while(1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        
        char client_ip[INET_ADDRSTRLEN];
        int client_port = ntohs(address.sin_port);
        inet_ntop(AF_INET, &(address.sin_addr), client_ip, INET_ADDRSTRLEN);
        
        add_client(client_ip, client_port);
        
        int valread = read(new_socket, buffer, BUFFER_SIZE);
        buffer[valread] = '\0';
        
        char fruit_name[50];
        int quantity;
        sscanf(buffer, "%s %d", fruit_name, &quantity);
        
        int fruit_index = find_fruit(fruit_name);
        char response[BUFFER_SIZE] = {0};
        
        if (fruit_index == -1) {
            strcpy(response, "Fruit not found");
        } else {
            if (fruits[fruit_index].quantity >= quantity) {
                fruits[fruit_index].quantity -= quantity;
                fruits[fruit_index].last_sold = time(NULL);
                sprintf(response, "Purchase successful. Remaining %s: %d", fruit_name, fruits[fruit_index].quantity);
            } else {
                sprintf(response, "Not enough %s available. Requested: %d, Available: %d", fruit_name, quantity, fruits[fruit_index].quantity);
            }
        }
        
        send(new_socket, response, strlen(response), 0);
        
        display_clients();
        printf("Total unique customers: %d\n", client_count);
        
        close(new_socket);
    }
    
    close(server_fd);
    return 0;
}