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
#define MAX_LISTEN 128
#define BUFFER_SIZE 128

int main()
{
    /* 创建套接字的句柄 */
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1)
    {
        perror("socket error");
        exit(-1);
    }

    struct sockaddr_in serverAddress;
    memset((void *)&serverAddress, 0, sizeof(serverAddress));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(SERVER_PORT);
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

    int serverAddressLen = sizeof(serverAddress);
    int ret = bind(sockfd, (struct sockaddr *)&serverAddress, serverAddressLen);
    if(ret == -1)
    {
        perror("bind error");
        exit(-1);
    }


    char buffer[BUFFER_SIZE];
    memset(buffer, 0, sizeof(char) * BUFFER_SIZE);

    int readBytes = 0;
    while(1)
    {
        readBytes = recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, 0);
        if(readBytes > 0)
        {
            printf("recv buffer:%s\n", buffer);
            for (int idx = 0; idx < readBytes; idx++)
            {
#if 0
                if (buffer[idx] >= 'a' && buffer[idx] <= 'z')
                {
                    buffer[idx] -= 32;
                }
#else
                buffer[idx] = toupper(buffer[idx]);
#endif
            }
        }
        sendto(sockfd, buffer, sizeof(buffer), 0, NULL, 0);
    }

    /* 关闭通信句柄 */
    close(sockfd);

    return 0;
}