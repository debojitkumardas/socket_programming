#include "utility_func.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {

    int server_socket_FD = GetSocket(AF_INET, SOCK_STREAM);

    struct sockaddr_in server_node;
    GetIPPort(&server_node, 9002);

    BindServer(server_socket_FD, &server_node, sizeof(server_node));

    ListenServer(server_socket_FD, 5);

    /*
    int client_socket_FD = AcceptConnection(server_socket_FD);

    char msg[1024] = "Hello, welcome to the server!!\n";

    int send_ret = SendMsg(client_socket_FD, msg, sizeof(msg));

    printf("%d bytes send.\n", send_ret);

    while (1) {
        int recv_ret = RecvMsg(client_socket_FD, msg, sizeof(msg));

        if (recv_ret > 0)
            printf("%d bytes received; Response: %s\n", recv_ret, msg);
        else
            break;
    }

    CloseServer(server_socket_FD);
    CloseServer(client_socket_FD);
    */

    ClientServers* client_details = AcceptConnection_n(server_socket_FD);

    char msg[1024] = "Hello, welcome to the server!!\n";

    int send_ret = SendMsg(client_details->client_socket_FD, msg, sizeof(msg));

    printf("%d bytes send.\n", send_ret);

    while (1) {
        int recv_ret = RecvMsg(client_details->client_socket_FD, msg, sizeof(msg));

        if (recv_ret > 0)
            printf("%d bytes received; Response: %s\n", recv_ret, msg);
        else
            break;
    }

    CloseServer(server_socket_FD);
    CloseServer(client_details->client_socket_FD);

    free(client_details);

    return 0;
}
