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
#define LOCAL_ADDRESS "172.27.105.168"
#define BUFFER_SIZE 128

// void sigHander(int sigNum)
// {

// }

int main()
{
    /* 信号注册 */
    // signal(SIGINT, sigHander);
    // signal(SIGQUIT, sigHander);
    // signal(SIGTSTP, sigHander);

    /* 创建socket套接字 */
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1)
    {
        perror("socket error");
        exit(-1);
    }
    
    /* 绑定 */
#if 0
    /* 这个结构体不好用 */
    struct sockaddr localAddress;
#else
    struct sockaddr_in localAddress;
#endif
    /* 清除脏数据 */
    memset(&localAddress, 0, sizeof(localAddress));

    /* 地址族 */
    localAddress.sin_family = AF_INET;
    /* 端口需要转成大端 */
    localAddress.sin_port = htons(SERVER_PORT);
    /* ip地址需要转成大端 */

    /* Address to accept any incoming messages.  */
    /* INADDR_ANY =  0x00000000 */
    localAddress.sin_addr.s_addr = htonl(INADDR_ANY);


    int localAddressLen = sizeof(localAddress); 
    int ret = bind(sockfd, (struct sockaddr *)&localAddress, localAddressLen);
    if(ret == -1)
    {
        perror("bind error");
        exit(-1);
    }

    /* 监听 */
    ret = listen(sockfd, MAX_LISTEN);
    if(ret == -1)
    {
        perror("listen error");
        exit(-1);
    }

    /* 客户的信息 */
    struct sockaddr_in clientAddress;
    memset(&clientAddress, 0, sizeof(clientAddress));

    socklen_t clientAddressLen = 0;
    int acceptfd = accept(sockfd, (struct sockaddr *)&clientAddress, &clientAddressLen);
    if(acceptfd == -1)
    {
        perror("accept error");
        exit(-1);
    }

    char buffer[BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer));

    char replybuffer[BUFFER_SIZE];
    memset(replybuffer, 0, sizeof(replybuffer));

    int readBytes = 0;
    while(1)
    {
        readBytes = read(acceptfd, buffer, sizeof(buffer));
        if(readBytes < 0)
        {
            perror("read error");
            close(acceptfd);
            break;
        }
        else
        {
            /* 读到的字符串 */
            printf("buffer:%s\n", buffer);

            sleep(3);

            strncpy(replybuffer, "hhh", sizeof(replybuffer) - 1);
            write(acceptfd, replybuffer, sizeof(replybuffer));
        }
    }

    close(sockfd);

    return 0;
}