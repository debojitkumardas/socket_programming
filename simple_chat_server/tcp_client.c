#include "utility_func.h"
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {

    int client_socket = get_socket();  // assigning an endpoint for client

    // assign IP and port
    struct sockaddr_in client_addr;
    get_IP_port(&client_addr, 9005);

    // where to connect to
    struct sockaddr_in server_addr;
    get_IP_port(&server_addr, 9002);

    // bind the socket to IP and port
    bind_server(client_socket, &client_addr, sizeof(client_addr));

    // connet to server
    connect_to_server(client_socket, &server_addr, sizeof(server_addr));

    // response
    char msg[1024];

    int recv_ret = recv_msg(client_socket, msg, sizeof(msg));

    printf("The response is: %s\n", msg);
    printf("The number of bytes received: %d\n", recv_ret);

    close_server(client_socket);

    return 0;
}
