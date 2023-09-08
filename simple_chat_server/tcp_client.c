#include "utility_func.h"
#include <stdio.h>
#include <string.h>

int main(void) {

    int client_socket_FD = GetSocket(AF_INET, SOCK_STREAM);

    // get Port and IP
    // struct sockaddr_in node;
    // GetIPPort(&node, 9005);

    // BindServer(socket_FD, &node, sizeof(node));

    // connect to server @Port
    struct sockaddr_in server_node;
    GetIPPort(&server_node, 9002);

    ConnectToServer(client_socket_FD, &server_node, sizeof(server_node));

    char msg[1024];

    int recv_ret = RecvMsg(client_socket_FD, msg, sizeof(msg));

    printf("Response received: %s\n", msg);
    printf("%d bytes received.\n", recv_ret);

    printf("Start chatting, type exit to exit.\n");
    while (1) {
        int ch;
        int i = 0;

        printf("Message: ");
        while ((ch = getchar()) != EOF && (ch != '\n')) {
            if (i < 1024) {
                msg[i] = ch;
            }
            else
                break;
            ++i;
        }

        if (i > 0) {
            if (i < 1024)
                msg[i] = '\0';

            if (strcmp(msg, "exit") == 0) {
                printf("Exiting!!\n");
                break;
            }

            int send_ret = SendMsg(client_socket_FD, msg, sizeof(msg));
            printf("Message sent. %d bytes sent.\n\n", send_ret);
        }
    }

    return 0;
}
