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
#include <json-c/json.h>
#include <json-c/json_object.h>

#define SERVER_PORT 8080
#define SERVER_ADDRESS "172.27.105.168"
#define BUFFER_SIZE 128

int main()
{
    /* 新建json对象 */
    struct json_object *object = json_object_new_object();
    if(object == NULL)
    {
        /* todo */
    }

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd == -1)
    {
        perror("socket error");
        exit(-1);
    }

    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(SERVER_PORT);

    int ret = inet_pton(AF_INET, SERVER_ADDRESS, (void *)(&serverAddress.sin_addr.s_addr));
    if(ret == -1)
    {
        perror("inet_pton error");
        exit(-1);
    }

    char buffer[BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer));

    char recvBuffer[BUFFER_SIZE];
    memset(recvBuffer, 0, sizeof(recvBuffer));

    struct json_object * wayVal = json_object_new_int64(1);
    json_object_object_add(object, "way", wayVal);

    /* 将json对象转成字符串 */
    const char * ptr = json_object_to_json_string(object);

    /* 发送字符串 */
    sendto(sockfd, ptr, strlen(ptr), 0, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    struct sockaddr socketAddress;
    memset(&socketAddress, 0, sizeof(socketAddress));

    socklen_t sockAddressLen = sizeof(socketAddress);
    recvfrom(sockfd, recvBuffer, sizeof(recvBuffer), 0, (struct sockaddr*)&socketAddress, &sockAddressLen);
    printf("recvBuffer: %s\n", recvBuffer);

    /* 关闭通信句柄 */
    close(sockfd);

    /* 释放json对象 */
    json_object_put(object);
    return 0;
}