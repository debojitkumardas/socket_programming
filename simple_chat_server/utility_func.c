#include "utility_func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>

void error_hand(char text[], const int ret_val) {

    // basic text manipulation **********************************************************
    char ch[] = " failed";
    char *temp = text;
    int len = 0, sz = strlen(ch);

    while (*temp != '\0') {
        len++;
        temp++;
    }

    char *text_old = malloc(sizeof(char) * (len + 1));
    char *text_new = malloc(sizeof(char) * (len + sz + 1));

    temp = text;
    int i = 0;
    while (*temp != '\0') {
        text_old[i] = *temp;
        text_new[i] = *temp;
        i++;
        temp++;
    }

    strcat(text_new, " failed");
    // basic text manipulation end ******************************************************

    if (ret_val == -1) {
        perror(text_new);
        exit(1);
    }
    else
        printf("%s successful.\n The return value is: %d\n",text_old, ret_val);

    free(text_old);
    free(text_new);
}

int get_socket() {

    const int server_socket = socket(AF_INET, SOCK_STREAM, 0);  // assign an endpoint to server

    // if socket assignment fails
    error_hand("Socket assignment", server_socket);

    return server_socket;
}

void get_IP_port(struct sockaddr_in *server_addr, unsigned port) {

    (*server_addr).sin_family = AF_INET;
    (*server_addr).sin_port = htons(port);
    (*server_addr).sin_addr.s_addr = INADDR_ANY;
    bzero(&((*server_addr).sin_zero), sizeof((*server_addr).sin_zero));
}

void bind_server(int server_socket, struct sockaddr_in *server_addr, unsigned len) {

    // bind the server to the IP and port
    const int bind_ret = bind(server_socket, (struct sockaddr *)server_addr, len);

    // if bind fails
    error_hand("Bind", bind_ret);
}

void listen_server(unsigned const server_socket, unsigned const backlog) {

    const int listen_ret = listen(server_socket, backlog);

    // if listen fails
    error_hand("Listen", listen_ret);
}

int accept_connection(int server_socket) {

    // to log client's info
    struct sockaddr_in client_addr;
    unsigned int size_client_addr = sizeof(client_addr);

    int accept_ret = accept(server_socket, (struct sockaddr *)&client_addr, &size_client_addr);

    // if accept fails
    error_hand("Accept", accept_ret);

    // client details
    printf(
        "Client's server details.\n"
        "sin_family: %d\n"
        "sin_port: %d\n"
        "sin_addr.s_addr: %d\n",
        client_addr.sin_family, ntohs(client_addr.sin_port), client_addr.sin_addr.s_addr
    );

    return accept_ret;
}

void connect_to_server(int server_socket, struct sockaddr_in *server_addr, unsigned len) {

    int connect_ret = connect(server_socket, (struct sockaddr *)server_addr, len);

    // if connect fails
    error_hand("Connect", connect_ret);
}

int send_msg(int client_socket, char *text, unsigned len) {

    int send_ret = send(client_socket, text, len, 0);

    // if message not sent
    error_hand("Send", send_ret);

    return send_ret;
}

int recv_msg(int client_socket, char *text, unsigned len) {

    int recv_ret = recv(client_socket, text, len, 0);

    // if receive fails
    error_hand("Receive", recv_ret);

    return recv_ret;
}

void close_server(int server_socket) {

    close(server_socket);
}
