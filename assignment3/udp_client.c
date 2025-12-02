#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
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
    
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Socket creation error");
        return -1;
    }
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("10.0.0.1");
    
    char message[BUFFER_SIZE] = {0};
    sprintf(message, "%s %d", fruit_name, quantity);
    
    socklen_t len = sizeof(serv_addr);
    sendto(sock, message, strlen(message), 0, (struct sockaddr *)&serv_addr, len);
    
    int valread = recvfrom(sock, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&serv_addr, &len);
    buffer[valread] = '\0';
    printf("%s\n", buffer);
    
    close(sock);
    return 0;
}