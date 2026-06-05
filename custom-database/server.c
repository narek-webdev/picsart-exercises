#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define DATABASE "database.txt"
#define PORT 8002
#define IP_ADDR "127.0.0.1"
#define COMMAND_SIZE 1000
#define COMMAND_ERROR "Command is not valid"

// GET ALL
// GET 2
// POST Carrot

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int checkCommandValidity (char command[COMMAND_SIZE])
{
	//Check for GET command
	if (command[3] == ' ')
	{
		char get_name[3] = {0};

		for (int i = 0; i < 3; ++i) {
			get_name[i] = command[i];
		}

		if (strcmp(get_name, "GET") != 0) {
			return 0;
		}

		return 1;
	}

	//Check for POST command
	if (command[4] == ' ')
	{
		char post_name[5] = {0};

		for (int i = 0; i < 4; ++i) {
			post_name[i] = command[i];
		}

		if (strcmp(post_name, "POST") != 0) {
			return 0;
		}

		return 1;
	}

	return 0;
}

void handleGetRequest (char command[COMMAND_SIZE], int client_fd)
{
	FILE * stream = fopen(DATABASE, "r");

	if (stream == NULL)
	{
		perror("fopen");
		close(client_fd);
		return;
	}

	if (fseek(stream, 0, SEEK_END) != 0)
	{
		perror("fseek");
		close(client_fd);
		fclose(stream);
		return;
	}

	long size = ftell(stream);

	if (size == -1)
	{
		perror("ftell");
		close(client_fd);
		fclose(stream);
		return;
	}

	rewind(stream);

	char * buffer = malloc(size + 1);

	if (buffer == NULL) {
		perror("malloc");
		close(client_fd);
		fclose(stream);
		return;
	}

	if (strcmp(command, "GET ALL") == 0)
	{
		size_t items_read = fread(buffer, sizeof(char), size, stream);

		if (items_read < size) {
			fprintf(stderr, "fread: expected %ld bytes, got %zu\n", size, items_read);
            free(buffer);
            fclose(stream);
            close(client_fd);
            return;
		}

		buffer[items_read] = '\0';

		if (send(client_fd, buffer, size, 0) < 0) {
			perror("send");
            free(buffer);
            fclose(stream);
            close(client_fd);
            return;
		}
	} else {
		char id[COMMAND_SIZE];
		sscanf(command, "GET %s", id);

		while (fgets(buffer, size + 1, stream) != NULL)
		{
			if (strncmp(buffer, id, strlen(id)) == 0)
			{
				if (send(client_fd, buffer, strlen(buffer), 0) < 0) {
					perror("send");
		            free(buffer);
		            fclose(stream);
		            close(client_fd);
		            return;
				}
			}
		}
	}

	free(buffer);
	fclose(stream);
}

void handlePostRequest (char command[COMMAND_SIZE], int client_fd)
{
	FILE * stream = fopen(DATABASE, "a");

	if (stream == NULL)
	{
		perror("fopen");
		close(client_fd);
		return;
	}

	int k = 5;
	char data[100] = {0};
	int i = 0;

	while (command[k] != '\0')
	{
		data[i] = command[k];
		printf("%c\n", command[k]);
		++k;
		++i;
	}

    fprintf(stream, "This is a new entry");

	fclose(stream);
	close(client_fd);
}

void * worker (void * arg)
{
	int client_fd = *(int *)arg;

	char command[COMMAND_SIZE] = {0};

	ssize_t bytes = recv(client_fd, command, sizeof(command) - 1, 0);
	
	if (bytes < 0)
	{
		perror("recv");
		free(arg);
		close(client_fd);
		return NULL;
	}

	command[bytes] = '\0';

	if (checkCommandValidity(command) == 0)
	{
		send(client_fd, COMMAND_ERROR, strlen(COMMAND_ERROR), 0);
		free(arg);
		close(client_fd);
		return NULL;
	}

	pthread_mutex_lock(&mutex);
	if (command[0] == 'G') {
		handleGetRequest(command, client_fd);
	} else {
		handlePostRequest(command, client_fd);
	}
	pthread_mutex_unlock(&mutex);

	free(arg);
	close(client_fd);

	return NULL;
}

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

	if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		perror("bind");
		close(sockfd);
		return 1;
	}

	if (listen(sockfd, SOMAXCONN) < 0)
	{
		perror("listen");
		close(sockfd);
		return 1;
	}

	printf("Server is listening \n");

	while (1)
	{
		struct sockaddr_in client_addr;

		socklen_t client_len = sizeof(client_addr);
		int client_fd = accept(sockfd, (struct sockaddr *)&client_addr, &client_len);

		if (client_fd < 0) {
			perror("accept");
			continue;
		}

		int * client_fd_ptr = malloc(sizeof(int));

		if (client_fd_ptr == NULL)
		{
			perror("malloc");
			close(client_fd);
			continue;
		}

		* client_fd_ptr = client_fd;

		pthread_t t1;

		if (pthread_create(&t1, NULL, worker, client_fd_ptr))
		{
			perror("pthread_create");
			close(*client_fd_ptr);
			free(client_fd_ptr);
			continue;
		}

		pthread_detach(t1);
	}

	return 0;
}