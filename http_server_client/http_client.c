#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {

    char *address;
    if (argc > 1)
        address = argv[1];
    else {
        perror("Enter the appropritate number of commandline arguments.\n");
        exit(-1);
    }

    int client_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in remote_addr;
    remote_addr.sin_family = AF_INET;
    remote_addr.sin_port = htons(80);
    inet_aton(address, &(remote_addr.sin_addr));

    int ret_val_connect = connect(client_socket, (struct sockaddr *)&remote_addr, sizeof(remote_addr));
    if (ret_val_connect == -1) {
        perror("Error connect.\n");
        exit(-1);
    }

    char request[] = "GET / HTTP/1.1\r\n\n";
    char response[10000];

    send(client_socket, request, sizeof(request), 0);
    recv(client_socket, response, sizeof(response), 0);

    printf("response from the server: %s\n", response);
    close(client_socket);

    return 0;
}
