#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

     // 創建socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

      // 綁定地址
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    //綁定失敗顯示error
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    //開始監聽
    if (listen(server_fd, 3) < 0) {
        perror("Listen");
        exit(EXIT_FAILURE);
    }

     // 接受連線
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
                            (socklen_t*)&addrlen)) < 0) {
        perror("Accept");
        exit(EXIT_FAILURE);
    }

     // 處理client端命令
    while (1) {
        int valread = read(new_socket, buffer, BUFFER_SIZE);
        buffer[valread] = '\0';

        if (strncmp(buffer, "add", 3) == 0) {
        int x, y;
        sscanf(buffer, "add %d %d", &x, &y);
        sprintf(buffer, "%d\n", x + y);
        send(new_socket, buffer, strlen(buffer), 0);
    } 
    
    else if (strncmp(buffer, "abs", 3) == 0) {
        int x;
        sscanf(buffer, "abs %d", &x);
        sprintf(buffer, "%d\n", abs(x));
        send(new_socket, buffer, strlen(buffer), 0);
    } 
    
    else if (strncmp(buffer, "mul", 3) == 0) {
        int x, y;
        sscanf(buffer, "mul %d %d", &x, &y);
        sprintf(buffer, "%d\n", x * y);
        send(new_socket, buffer, strlen(buffer), 0);
    } 
    
    else if (strncmp(buffer, "kill", 4) == 0) {
        
        close(new_socket);  
        exit(0); 
    }else {
            send(new_socket, "Hello\n", 17, 0);
        }
    }
   //關閉連線
    close(new_socket);
    close(server_fd);
    return 0;
}

