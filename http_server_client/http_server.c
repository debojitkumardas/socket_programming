#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>

int main(void) {

    FILE *html_data;
    html_data = fopen("index.html", "r");

    char response_data[1024];
    fgets(response_data, sizeof(response_data), html_data);

    char http_header[2048] = "HTTP/1.1 200 OK\r\n\n";
    strcat(http_header, response_data);

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8001);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(server_addr.sin_zero), sizeof(server_addr.sin_zero));

    int ret_val_bind = bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (ret_val_bind == -1) {
        perror("Error bind.\n");
        exit(-1);
    }

    int ret_val_listen = listen(server_socket, 5);
    if (ret_val_listen == -1) {
        perror("Error listen.\n");
        exit(-1);
    }

    int client_socket;
    while (1) {
        client_socket = accept(server_socket, NULL, NULL);
        send(client_socket, http_header, sizeof(http_header), 0);
        close(client_socket);
    }

    return 0;
}
