#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // for close() function
#include <arpa/inet.h>  // for socket functions
#include <sys/socket.h>

//Here are the basic steps we'll follow:

//Create a socket.
//Bind it to an IP address and port.
//Listen for incoming connections.
//Accept connections.
//Send a basic HTTP response.
//Close the connection.

int main() {
    int server_fd;
    
    //int socket(int domain, int type, int protocol);
    // Create a TCP socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }
    
    printf("Socket created successfully!\n");

    return 0;
}
