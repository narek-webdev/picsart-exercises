#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8081
#define MAX_CLIENTS 10
#define BUFFER_SIZE 4096

int clients[MAX_CLIENTS];
int client_count = 0;

pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

void broadcast_message(char * message, int sender_fd) {
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < client_count; ++i) {
        if (clients[i] != sender_fd) {
            if (send(clients[i], message, strlen(message), 0) < 0) {
                perror("Message send error");
                continue;
            }
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

void * handle_client (void * arg) {
    int clientSocket = *((int*) arg);

    free(arg);

    char buffer[BUFFER_SIZE] = {0};
    int bytesRead = 0;
    
    while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytesRead] = '\0';
        broadcast_message(buffer, clientSocket);
    }

    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < client_count; ++i) {
        if (clients[i] == clientSocket) {
            clients[i] = clients[client_count - 1];
            client_count--;
            close(clientSocket);
            break;
        }
    }
    pthread_mutex_unlock(&clients_mutex);

    return NULL;
}

int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket < 0) {
        perror("Socket open error");
        exit(1);
    }

    int opt = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    int * new_sock;

    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
        perror("Bind error");
        close(serverSocket);
        return 1;
    }

    if (listen(serverSocket, 10) < 0)
    {
        perror("listen");
        close(serverSocket);
        return 1;
    }

    printf("Server running on PORT: %d\n", PORT);

    while (1) {
        int client_fd = accept(serverSocket, NULL, NULL);

        if (client_fd < 0)
        {
            perror("accept");
            continue;
        }

        new_sock = (int*)malloc(sizeof(int));

        if (new_sock == NULL)
        {
            perror("malloc");
            continue;
        }

        *new_sock = client_fd;

        pthread_mutex_lock(&clients_mutex);

        if (client_count >= MAX_CLIENTS) {
            printf("Max clients reached. Connection rejected.\n");
            close(client_fd);
            free(new_sock);
            pthread_mutex_unlock(&clients_mutex);
            continue;
        }

        clients[client_count++] = client_fd;

        pthread_mutex_unlock(&clients_mutex);

        pthread_t tid;

        if (pthread_create(&tid, NULL, handle_client, new_sock))
        {
            perror("pthread_create");
            pthread_mutex_lock(&clients_mutex);
            client_count--;
            pthread_mutex_unlock(&clients_mutex);
            close(client_fd);
            free(new_sock);
        } else {
            pthread_detach(tid);
        }
    }

    return 0;
}