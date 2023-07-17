#ifndef UTILITY_FUNC_H
#define UTILITY_FUNC_H

#include <netinet/in.h>

void error_hand(char text[], const int ret_val);
int get_socket();
void get_IP_port(struct sockaddr_in *server_addr, unsigned port);
void bind_server(int server_socket, struct sockaddr_in *server_addr, unsigned len);
void listen_server(unsigned const server_socket, unsigned const backlog);
int accept_connection(int server_socket);
void connect_to_server(int server_socket, struct sockaddr_in *server_addr, unsigned len);
int send_msg(int client_socket, char *text, unsigned len);
int recv_msg(int client_socket, char *text, unsigned len);
void close_server(int server_socket);

#endif // !UTILITY_FUNC_H
