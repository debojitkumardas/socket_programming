#ifndef UTILITY_FUNC_H
#define UTILITY_FUNC_H

#include <netinet/in.h>

typedef struct ClientServers ClientServers;

struct ClientServers {
    int client_socket_FD;
    struct sockaddr_in address;
    int error;
    int flag;  // yes (succes) or no (failed)
};

/** To handle error */
void ErrorHand(char text[], const int ret_val);
/** Get socket file descriptor */
int GetSocket(int domain, int type);
void GetIPPort(struct sockaddr_in *server_addr, unsigned port);
void BindServer(int server_socket, struct sockaddr_in *server_addr, unsigned short len);
void ListenServer(unsigned const server_socket, unsigned const backlog);
int AcceptConnection(int server_socket);
ClientServers* AcceptConnectionN(int server_socket);
void ConnectToServer(int server_socket, struct sockaddr_in *server_addr, unsigned len);
int SendMsg(int client_socket, char *text, unsigned len);
int RecvMsg(int client_socket, char *text, unsigned len);
void CloseServer(int server_socket);

void AcceptConnectionNUtil(int server_socket);
void AcceptIncomingConnection(int server_socket_FD);

#endif // !UTILITY_FUNC_H
