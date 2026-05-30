#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT_NUMBER 9090
#define IP_ADDR "127.0.0.1"
#define STR_LEN 4

char * reverse_str (char *, int);

int main ()
{

int sockfd;

if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
 printf("Open socket Error\n");
 return 1;
}

struct sockaddr_in server_addr;
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(PORT_NUMBER);

if (inet_pton(AF_INET, IP_ADDR, &server_addr.sin_addr) <= 0) {
 printf("Inet pton Error\n");
 return 1;
}

if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
 printf("Bind Error\n");
 return 1;
}

if (listen(sockfd, SOMAXCONN) < 0) {
 printf("Listen Error\n");
 return 1;
}

struct sockaddr_in client_addr;
socklen_t addr_len = sizeof(client_addr);
int client_fd = accept(sockfd, (struct sockaddr *)&client_addr, &addr_len);

if (client_fd < 0) {
 printf("Client fd Error\n");
 return 1;
}

char str[STR_LEN] = {0};
if (recv(client_fd, str, STR_LEN, 0) < 0)
{
 printf("Recv error\n");
 return 1;
}

printf("From client: %s\n", str);

if (send(client_fd, reverse_str(str, strlen(str)), STR_LEN, 0) < 0) {
 printf("Send Error\n");
 return 1;
}

if (close(client_fd) < 0) {
 printf("Error\n");
 return 1;
}

if (close(sockfd) < 0) {
 printf("Error\n");
 return 1;
}

return 0;
}

char * reverse_str (char * str, int size)
{
 int l = 0;
 int r = size - 1;
 
 while (r > l) {
  int tmp = str[l];
  str[l] = str[r];
  str[r] = tmp;
  
  ++l;
  --r;
 } 
 
 return str;
}