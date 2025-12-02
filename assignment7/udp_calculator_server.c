#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <math.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    
    server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_fd == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    printf("UDP Calculator Server listening on port %d\n", PORT);
    
    while(1) {
        struct sockaddr_in client_addr;
        int client_len = sizeof(client_addr);
        
        int valread = recvfrom(server_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &client_len);
        if (valread > 0) {
            buffer[valread] = '\0';
            
            char operation[20];
            double num1, num2, result;
            int operands = sscanf(buffer, "%s %lf %lf", operation, &num1, &num2);
            
            char response[BUFFER_SIZE] = {0};
            
            if (strcmp(operation, "sin") == 0) {
                result = sin(num1);
                sprintf(response, "sin(%.2f) = %.6f", num1, result);
            } else if (strcmp(operation, "cos") == 0) {
                result = cos(num1);
                sprintf(response, "cos(%.2f) = %.6f", num1, result);
            } else if (strcmp(operation, "tan") == 0) {
                result = tan(num1);
                sprintf(response, "tan(%.2f) = %.6f", num1, result);
            } else if (strcmp(operation, "inv") == 0) {
                if (num1 != 0) {
                    result = 1.0 / num1;
                    sprintf(response, "1/%.2f = %.6f", num1, result);
                } else {
                    strcpy(response, "Error: Division by zero");
                }
            } else if (strcmp(operation, "+") == 0 && operands == 3) {
                result = num1 + num2;
                sprintf(response, "%.2f + %.2f = %.2f", num1, num2, result);
            } else if (strcmp(operation, "-") == 0 && operands == 3) {
                result = num1 - num2;
                sprintf(response, "%.2f - %.2f = %.2f", num1, num2, result);
            } else if (strcmp(operation, "*") == 0 && operands == 3) {
                result = num1 * num2;
                sprintf(response, "%.2f * %.2f = %.2f", num1, num2, result);
            } else if (strcmp(operation, "/") == 0 && operands == 3) {
                if (num2 != 0) {
                    result = num1 / num2;
                    sprintf(response, "%.2f / %.2f = %.2f", num1, num2, result);
                } else {
                    strcpy(response, "Error: Division by zero");
                }
            } else {
                strcpy(response, "Error: Invalid operation");
            }
            
            sendto(server_fd, response, strlen(response), 0, (struct sockaddr *)&client_addr, client_len);
            printf("Processed request from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        }
    }
    
    close(server_fd);
    return 0;
}