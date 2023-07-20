#include "utility_func.h"
#include <stdio.h>

int main(void) {

    int socket_FD = get_socket(AF_INET, SOCK_STREAM);

    struct sockaddr_in node;
    get_IP_port(&node, 9002);

    bind_server(socket_FD, &node, sizeof(node));

    listen_server(socket_FD, 5);

    int accept_ret = accept_connection(socket_FD);

    char msg[1024] = "Hello, welcome to the server!!\n";

    int send_ret = send_msg(accept_ret, msg, sizeof(msg));

    printf("%d bytes send.\n", send_ret);

    close_server(socket_FD);

    return 0;
}
