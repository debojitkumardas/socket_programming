#include "utility_func.h"
#include <stdio.h>

int main(void) {

    int server_socket = get_socket();  // assign an endpoint to server

    // assign IP and port to that server
    struct sockaddr_in server_addr;
    get_IP_port(&server_addr, 9002);

    // bind server to an IP and port
    bind_server(server_socket, &server_addr, sizeof(server_addr));

    // listen for any connection
    listen_server(server_socket, 5);

    // accepting the connection
    int accept_ret = accept_connection(server_socket);

    char msg[1024];

    int msg_ret = get_message(msg, sizeof(msg));

    printf("%d bytes in the message.\n", msg_ret);

    int send_ret = send_msg(accept_ret, msg, sizeof(msg));

    printf("%d bytes of data send.\n", send_ret);

    // closing the connection
    close_server(server_socket);

    return 0;
}
