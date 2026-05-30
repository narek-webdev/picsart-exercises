#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT_ADDR 9090
#define IP_ADDR "127.0.0.1"
#define BUFF_SIZE 1024

int main()
{
    int sockfd;
    
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket");
        return 1;
    }
    
    struct sockaddr_in client_addr;
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(PORT_ADDR);
    
    if (inet_pton(AF_INET, IP_ADDR, &client_addr.sin_addr) <= 0)
    {
        perror("inet_pton");
        return 1;
    }
    
    socklen_t addrlen = sizeof(client_addr);
    if (connect(sockfd, (struct sockaddr *)&client_addr, addrlen) < 0)
    {
        perror("connect");
        return 1;
    }
    
    const char * str = "racecar";
    if (send(sockfd, str, strlen(str), 0) < 0)
    {
        perror("send");
        return 1;
    }

    char value[BUFF_SIZE] = {0};
    if (recv(sockfd, value, BUFF_SIZE, 0) < 0) {
     perror("recv");
     return 1;
    }
    
    printf("Check: %s\n", value);
    
    if (close(sockfd) < 0)
    {
        perror("close");
        return 1;
    }
    
    return 0;
}
