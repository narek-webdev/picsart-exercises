#include <stdio.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
   
#define PORT 8080
#define LOCALHOST "127.0.0.1"

void * worker (void * arg) {
    int client_fd = *(int *)arg;
    free(arg);
	
    printf("Worker is working...\n");
     
    close(client_fd);
    return NULL;
}

int main ()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sockfd < 0) {
        perror("socket");
        return 1;
    }
    
    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    
    if (inet_pton(AF_INET, LOCALHOST, &server_addr.sin_addr) <= 0) {
        perror("inet_pton");
        return 1;
    }
    
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        return 1;
    }
    
    if (listen(sockfd, SOMAXCONN) < 0) {
        perror("listen");
        return 1;
    }
    
    while (1) {
        struct sockaddr_in client_addr = {0};
        socklen_t addrlen = sizeof(client_addr);

        int client_fd = accept(sockfd, (struct sockaddr *)&client_addr, &addrlen);
        
        if (client_fd < 0) {
            perror("accept");
            continue;
        }
        
        int * fd_ptr = malloc(sizeof(int));
        
        if (fd_ptr == NULL) {
            perror("malloc");
            close(client_fd);
            continue; 
        }

        *fd_ptr = client_fd;
        
        pthread_t thread;
        
        if (pthread_create(&thread, NULL, worker, fd_ptr)) {
            perror("pthread_create");
            close(client_fd);
            return 1;
        }
            
        if (pthread_detach(thread)) {
            perror("pthread_detach");
            return 1;
        }
    }

    close(sockfd);
    
    return 0;
}