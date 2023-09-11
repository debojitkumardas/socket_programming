#include "utility_func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

void ErrorHand(char text[], const int ret_val) {
    if (ret_val == -1) {
        printf("%s failed\n", text);
        exit(1);
    }
    /*
    else
        printf("%s successful.\n The return value is: %d\n", text, ret_val);
    */
}

int GetSocket(int domain, int type) {

    const int socket_FD = socket(domain, type, 0);  // assign an endpoint to server; 0 -> use IP layer

    // if socket assignment fails
    ErrorHand("Socket assignment", socket_FD);

    return socket_FD; // return the file descriptor
}

void GetIPPort(struct sockaddr_in *server_addr, unsigned port) {

    (*server_addr).sin_family = AF_INET;
    (*server_addr).sin_port = htons(port);
    (*server_addr).sin_addr.s_addr = INADDR_ANY;
    bzero(&((*server_addr).sin_zero), sizeof((*server_addr).sin_zero));
}

void BindServer(int server_socket, struct sockaddr_in *server_addr, unsigned short len) {

    // bind the server to the IP and port
    const int bind_ret = bind(server_socket, (struct sockaddr *)server_addr, len);

    // if bind fails
    ErrorHand("Bind", bind_ret);
}

void ListenServer(unsigned const server_socket, unsigned const backlog) {

    const int listen_ret = listen(server_socket, backlog);

    // if listen fails
    ErrorHand("Listen", listen_ret);
}

int AcceptConnection(int server_socket) {

    // to log client's info
    struct sockaddr_in client_addr;
    unsigned int size_client_addr = sizeof(client_addr);

    int client_socket_FD = accept(server_socket, (struct sockaddr*)&client_addr, &size_client_addr);

    // if accept fails
    ErrorHand("Accept", client_socket_FD);

    // client details
    size_t len = sizeof(client_addr);
    char* ip = malloc(len * sizeof(char));
    inet_ntop(AF_INET, &(client_addr.sin_addr.s_addr), ip, len);

    printf(
        "Client's server details.\n"
        "sin_family: %d\n"
        "sin_port: %d\n"
        "sin_addr.s_addr: %s\n",
        client_addr.sin_family, ntohs(client_addr.sin_port), ip
    );

    free(ip);

    return client_socket_FD;
}

ClientServers* AcceptConnectionN(int server_socket) {
    struct sockaddr_in client_addr;
    unsigned int size_client_addr = sizeof(client_addr);

    int client_socket_FD = accept(server_socket, (struct sockaddr*)&client_addr, &size_client_addr);

    ClientServers* client_details = malloc(sizeof(ClientServers));

    client_details->address = client_addr;
    client_details->client_socket_FD = client_socket_FD;

    if (client_socket_FD > 0) {
        client_details->flag = 1;
        client_details->error = 0;
    }
    else {
        client_details->flag = 0;
        client_details->error = client_socket_FD;
    }

    return client_details;
}

void ConnectToServer(int server_socket, struct sockaddr_in *server_addr, unsigned len) {

    int connect_ret = connect(server_socket, (struct sockaddr *)server_addr, len);

    // if connect fails
    ErrorHand("Connect", connect_ret);
}

int SendMsg(int client_socket, char *text, unsigned len) {

    int send_ret = send(client_socket, text, len, 0);

    // if message not sent
    ErrorHand("Send", send_ret);

    return send_ret;
}

int RecvMsg(int client_socket, char *text, unsigned len) {

    int recv_ret = recv(client_socket, text, len, 0);

    // if receive fails
    ErrorHand("Receive", recv_ret);

    return recv_ret;
}

void CloseServer(int server_socket) {

    close(server_socket);
}

void AcceptConnectionNUtil(int server_socket) {
    ClientServers* client_details = AcceptConnectionN(server_socket);
}

void AcceptIncomingConnection(int server_socket_FD) {
    pthread_t id;
    pthread_create(&id, NULL, AcceptConnectionNUtil, server_socket_FD);
}
