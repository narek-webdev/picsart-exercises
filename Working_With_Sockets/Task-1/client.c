#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORT_NUMBER 9090
#define IP_ADDR "127.0.0.1"
#define STR_LEN 4

int main ()
{
int sockfd;

if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
{
 printf("Error\n");
 return 1;
}

struct sockaddr_in client_addr;
client_addr.sin_family = AF_INET;
client_addr.sin_port = htons(PORT_NUMBER);

if (inet_pton(AF_INET, IP_ADDR, &client_addr.sin_addr) <= 0)
{
 printf("Error\n");
 return 1;
}

socklen_t addrlen = sizeof(client_addr);
if (connect(sockfd, (struct sockaddr *)&client_addr, addrlen) < 0)
{
 printf("Error\n");
 return 1;
}

char * str = "eax";
if (send(sockfd, str, STR_LEN, 0) < 0)
{
 printf("Send error\n");
 return 1;
}

char reversed[STR_LEN] = {0};
if (recv(sockfd, reversed, STR_LEN, 0) < 0)
{
 printf("Error\n");
 return 1;
}

printf("Reversed string: %s\n", reversed);

if (close(sockfd) < 0)
{
 printf("Error\n");
 return 1;
}

return 0;
}
