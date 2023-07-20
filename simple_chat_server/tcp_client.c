#include "utility_func.h"
#include <stdio.h>

int main(void) {

    int socket_FD = get_socket(AF_INET, SOCK_STREAM);

    // get Port and IP
    struct sockaddr_in node;
    get_IP_port(&node, 9005);

    bind_server(socket_FD, &node, sizeof(node));

    // to connect to
    struct sockaddr_in node_con;
    get_IP_port(&node, 9002);

    connect_to_server(socket_FD, &node_con, sizeof(node_con));

    char msg[1024];

    int recv_ret = recv_msg(socket_FD, msg, sizeof(msg));

    printf("Response received: %s\n", msg);
    printf("%d bytes received.\n", recv_ret);

    return 0;
}
