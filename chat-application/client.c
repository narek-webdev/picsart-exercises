#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

#define PORT 8081
#define MAX_EVENTS 2
#define BUFFER_SIZE 4096
#define IP_ADDR "127.0.0.1"

// #include <termios.h>
// #include <sys/select.h>
// #include <pthread.h>

int main() {
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (client_socket == -1)
    {
        perror("socket");
        return 1;
    }

    struct sockaddr_in client_addr;
    client_addr.sin_port = htons(PORT);
    client_addr.sin_family = AF_INET;

    if (inet_pton(AF_INET, IP_ADDR, &client_addr.sin_addr) <= 0)
    {
        perror("inet_pton");
        close(client_socket);
        return 1;
    }

    if (connect(client_socket, (struct sockaddr*) &client_addr, sizeof(client_addr)) < 0) {
        perror("Connection error");
        close(client_socket);
        return 1;
    }

    int ep = epoll_create1(EPOLL_CLOEXEC);

    if (ep < 0)
    {
        perror("epoll_create1");
        close(client_socket);
        return 1;
    }

    struct epoll_event ev, events[MAX_EVENTS];

    ev.events = EPOLLIN;
    ev.data.fd = client_socket;
    
    if (epoll_ctl(ep, EPOLL_CTL_ADD, client_socket, &ev) < 0)
    {
        perror("epoll_ctl");
        close(client_socket);
        return 1;
    }

    ev.events = EPOLLIN;
    ev.data.fd = STDIN_FILENO;
    
    if (epoll_ctl(ep, EPOLL_CTL_ADD, STDIN_FILENO, &ev) < 0)
    {
        perror("epoll_ctl");
        close(client_socket);
        return 1;
    }
    
    char buffer[BUFFER_SIZE] = {0};

    // struct termios oldt, newt;
    // tcgetattr(STDIN_FILENO, &oldt);
    // newt = oldt;
    // newt.c_lflag &= ~ICANON;
    // tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    int is_typing = 0;
    int timeout_ms = 1000;

    while (1) {
        int eventsCount = epoll_wait(ep, events, MAX_EVENTS, -1);

        if (eventsCount < 0)
        {
            perror("epoll_wait");
            break;
        }

        for (int i = 0; i < eventsCount; ++i) {
            if (events[i].data.fd == client_socket) {
                int bytes_read = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
                
                if (bytes_read <= 0)
                {
                    if (bytes_read == 0) {
                        printf("Server disconnected\n");
                    } else {
                        perror("recv");
                    }

                    close(ep);
                    close(client_socket);
                    return 1;
                }

                buffer[bytes_read] = '\0';
                
                printf(" -> %s", buffer);
            } else if (events[i].data.fd == STDIN_FILENO) {
                if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
                    perror("fgets");
                    break;
                }

                if (send(client_socket, buffer, strlen(buffer), 0) < 0)
                {
                    perror("send");
                    break;
                }
            }  
        }
    }

    return 0;
}