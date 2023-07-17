#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>

int main(void) {

    int socket_client_node = socket(AF_INET, SOCK_STREAM, 0);

    // specifing the IP and Port to connect to
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(server_addr.sin_zero), sizeof(server_addr.sin_zero));

    // connecting to the server
    int ret_val_connect = connect(socket_client_node, (struct sockaddr *)&server_addr, sizeof(server_addr));
    // ensuring that it's connected
    if (ret_val_connect == -1) {
        perror("Connect failed.\n");
        exit(-1);
    }
    else {
        printf("Connect successful. The return value is: %d\n", ret_val_connect);
        printf("Also the return value of socket is: %d\n", socket_client_node);
    }

    // receiving response from server
    char response[256];
    long int ret_val_recv = recv(socket_client_node, response, sizeof(response), 0);
    // printing the return value of recv
    // The return value for recv is just the size of the received buffer
    printf("The return value for recv is: %ld\n", ret_val_recv);

    // printing the response
    printf("Response: %s\n", response);

    close(socket_client_node);

    return 0;
}
