#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main(int argc, char const *argv[]) {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    char fruit_name[50];
    int quantity;
    
    if (argc != 3) {
        printf("Usage: %s <fruit_name> <quantity>\n", argv[0]);
        return -1;
    }
    
    strcpy(fruit_name, argv[1]);
    quantity = atoi(argv[2]);
    
    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "10.0.0.1", &serv_addr.sin_addr);
    
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    
    char message[BUFFER_SIZE] = {0};
    sprintf(message, "%s %d", fruit_name, quantity);
    send(sock, message, strlen(message), 0);
    
    int valread = read(sock, buffer, BUFFER_SIZE);
    buffer[valread] = '\0';
    printf("%s\n", buffer);
    
    close(sock);
    return 0;
}