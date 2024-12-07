#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(){

	int sock=0;
	struct sockaddr_in server_addr;
	char buffer[BUFFER_SIZE]={0};
	char command[BUFFER_SIZE];

        // 創建socket
	if((sock=socket(AF_INET,SOCK_STREAM,0))<0){
		perror("Socket creation error");
		return -1;
	}

	// 設定伺服器地址
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(PORT);

	// 轉換地址
	if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        perror("Invalid address or address not supported");
        return -1;
    }
	// 延遲1秒，給伺服器足夠時間啟動
	sleep(1);
	
	// 連接伺服器
	 if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        return -1;
   	 }	
	
	 // 從stdin讀取命令並發送到伺服器
	 while (fgets(command, BUFFER_SIZE, stdin) != NULL) {
        send(sock, command, strlen(command), 0);
        if (strncmp(command, "kill", 4) == 0) break;

	// 接收伺服器回覆
        int valread = read(sock, buffer, BUFFER_SIZE);
        buffer[valread] = '\0';
        printf("%s", buffer);
	 }

    close(sock);
    return 0;
}
