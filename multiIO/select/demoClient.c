#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#define SERVER_PORT 8080
#define SERVER_ADDRESS "172.27.105.168"
#define BUFFER_SIZE 128

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1)
    {
        perror("socket error");
        exit(-1);
    }

    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    /* 端口 */
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(SERVER_PORT);

    int ret = inet_pton(AF_INET, SERVER_ADDRESS, (void *)&(serverAddress.sin_addr.s_addr));
    if(ret != 1)
    {
        perror("inet_pton error");
        exit(-1);
    }

    /* ip地址 */
    ret = connect(sockfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    if(ret == -1)
    {
        perror("connect error");
        exit(-1);
    }

    /* 写缓冲区 */
    char writeBuffer[BUFFER_SIZE];
    memset(writeBuffer, 0, sizeof(writeBuffer));

    /* 读缓冲区 */
    char recvbuffer[BUFFER_SIZE];
    memset(recvbuffer, 0, sizeof(recvbuffer));

    int readBytes = 0;
    while(1)
    {   
        printf("input:");
        scanf("%s", writeBuffer);

        /* 带上字符串的结束符'\0' */
        write(sockfd, writeBuffer, strlen(writeBuffer) + 1);

        /* 接受数据 */
        readBytes = read(sockfd, recvbuffer, sizeof(recvbuffer));
        if(readBytes < 0)
        {
            perror("read error");
            exit(-1);
        }
        else if(readBytes == 0)
        {
            printf("readBytes == 0\n");
        }
        else
        {
            printf("recv: %s\n", recvbuffer);
        }
    }
    

    /* 休息5s */
    sleep(5);

    close(sockfd);
    
    return 0;
}