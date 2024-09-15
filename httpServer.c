#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // for close() function
#include <arpa/inet.h>  // for socket functions
#include <sys/socket.h>
#include <sys/types.h>

#define LISTEN_BACKLOG 50

int main() {
    int server_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    int port = 8080;

    // Create a TCP socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }

    // Define the server address
    server_addr.sin_family = AF_INET;  
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port); 

    // Bind the socket
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Failed to bind socket");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, LISTEN_BACKLOG) == -1) {
        perror("Failed to listen");
        exit(EXIT_FAILURE);
    }

    printf("Socket is listening on port %d\n", port);

    // Accept incoming connection
    int accRes = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
    if (accRes == -1) {
        perror("Failed to accept");
        exit(EXIT_FAILURE);
    } else {
        printf("Client has connected\n");

        // Prepare HTTP response
        char message[] = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 12\r\n\r\nHello world!";

        // Send the HTTP response to the client
        send(accRes, message, strlen(message), 0);

        // Close the client connection
        close(accRes);
        printf("Client connection closed\n");
    }

    // Keep the server socket open to listen for more connections
    close(server_fd);

    return 0;
}
