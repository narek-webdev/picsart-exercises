#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define PORT 8002
#define IP_ADDR "127.0.0.1"
#define BUFFER_SIZE 4096
#define COMMAND_SIZE 1000

int main ()
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0)
	{
		perror("socket");
		return 1;
	}

	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	
	if (inet_pton(AF_INET, IP_ADDR, &server_addr.sin_addr) <= 0)
	{
		perror("inet_pton");
		return 1;
	}

	if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		perror("connect");
		return 1;
	}

	char command[COMMAND_SIZE] = {0};

	printf("Write a command: ");

	if (fgets(command, sizeof(command), stdin) != NULL)
	{
		command[strcspn(command, "\n")] = '\0';
	}

	if (send(sockfd, command, strlen(command), 0) < 0)
	{
		perror("send");
		return 1;
	}

	char buff[BUFFER_SIZE] = {0};

	ssize_t bytes = recv(sockfd, buff, BUFFER_SIZE - 1, 0);
	
	if (bytes < 0) {
		perror("recv");
		close(sockfd);
		return 1;
	}

	buff[bytes] = '\0';

	printf("%s\n", buff);

	if (close(sockfd) < 0)
	{
		perror("close");
		return 1;
	}

	return 0;
}