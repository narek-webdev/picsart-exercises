#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT_ADDR 9090
#define IP_ADDR "127.0.0.1"
#define BUFF_SIZE 1024

char * palindrome (char *);

int main()
{
    int sockfd;
   
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket");
        return 1;
    }
    
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT_ADDR);
    
    if (inet_pton(AF_INET, IP_ADDR, &server_addr.sin_addr) <= 0)
    {
        perror("inet_pton");
        return 1;
    }
    
    socklen_t addrlen = sizeof(server_addr);
    if (bind(sockfd, (struct sockaddr *)&server_addr, addrlen) < 0)
    {
        perror("bind");
        return 1;
    }
    
    if (listen(sockfd, SOMAXCONN) < 0)
    {
        perror("listen");
        return 1;
    }
    
    struct sockaddr_in client_addr;
    socklen_t clientAddrlen = sizeof(client_addr);
    
    int client_fd = accept(sockfd, (struct sockaddr *)&client_addr, &clientAddrlen);
    
    if (client_fd < 0)
    {
        perror("accept");
        return 1;
    }
    
    char str[BUFF_SIZE] = {0};
    if (recv(client_fd, str, BUFF_SIZE, 0) < 0)
    {
        perror("recv");
        return 1;
    }

    char * value = palindrome(str);
    if (send(client_fd, value, strlen(value), 0) < 0) {
     perror("send");
     return 1; 
    }
    
    if (close(sockfd) < 0)
    {
        perror("close");
        return 1;
    }
    
    if (close(client_fd) < 0)
    {
        perror("close");
        return 1;
    }
   
    return 0;
}

char * palindrome (char * str)
{
    int l = 0;
    int r = strlen(str) - 1;
    
    while (l < r) {
        if (str[l] != str[r]) return "Not palindrome";
        ++l;
        --r;
    }
    
    return "Palindrome";
}
