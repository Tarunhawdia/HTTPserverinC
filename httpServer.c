#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // for close() function
#include <arpa/inet.h>  // for socket functions
#include <sys/socket.h>
#include <sys/types.h>

#define LISTEN_BACKLOG 50


//Here are the basic steps we'll follow:

//Create a socket.
//Bind it to an IP address and port.
//Listen for incoming connections.
//Accept connections.
//Send a basic HTTP response.
//Close the connection.

int main() {
    int server_fd;
    struct sockaddr_in server_addr;
    int port=8080;

    //int socket(int domain, int type, int protocol);
    // Create a TCP socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }

    // Define the server address
    server_addr.sin_family = AF_INET;  // IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY;  // Listen on any available network interface
    server_addr.sin_port = htons(port);  // Convert port number to network byte order


    // Bind the socket to the specified IP and port
    // 0 on sucess -1 on error
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Failed to bind socket");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if(listen(server_fd,LISTEN_BACKLOG)==-1){
        perror("Failed to listen");
        exit(EXIT_FAILURE);
    }

    printf("Socket is listining on port %d \n", port);

    return 0;
}
