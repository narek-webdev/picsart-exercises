#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT_ADDR 9090
#define IP_ADDR "127.0.0.1"

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
    
    struct sockaddr client_addr;
    socklen_t addrlen2 = sizeof(client_addr);
    int client_fd = accept(sockfd, (struct sockaddr *)&client_addr, &addrlen2);

    if (client_fd < 0)
    {
        perror("accept");
        return 1;
    }
    
    char filename[100] = {0};
    if (recv(client_fd, filename, 100, 0) < 0)
    {
        perror("recv");
        return 1;
    }

    FILE * stream = fopen(filename, "r");
    
    if (stream == NULL) {
      perror("fopen");
      return 1;
    }
 
    char file_buff[1024] = {0};
    int read_bytes = fread(file_buff, 1, sizeof(file_buff), stream);
    
    if (ferror(stream))
    {
        perror("fread");
        return 1;
    }

    fclose(stream);
    
    if (send(client_fd, file_buff, read_bytes, 0) < 0)
    {
        perror("send");
        return 1;
    }

    if (close(client_fd) < 0)
    {
        perror("close");
        return 1;
    }

    if (close(sockfd) < 0)
    {
        perror("close");
        return 1;
    }
    
    return 0;
}