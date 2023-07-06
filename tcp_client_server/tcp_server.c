#include <stdio.h>
#include <stdlib.h>  // for exit()
#include <strings.h>  // for bzero()
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>  // for close()
#include <errno.h>
#include <arpa/inet.h>
#include <stdarg.h>

#if NR
#define PADDING 4

void message_box(const char *msg) {

    int nc, MAX_W;
    const char *tmp_ptr = msg;
    char h_space[PADDING] = "    ";

    nc = 0;
    MAX_W = 0;
    while (*tmp_ptr != '\0') {
        if (*tmp_ptr == '\n' || *(tmp_ptr + 1) == '\0') {
            if (nc > MAX_W)
                MAX_W = nc;
            nc = 0;
        }
        else
            nc++;

        tmp_ptr++;
    }
}

void get_message(const char *format, ...) {
    va_list arg;
    char *msg;

    va_start (arg, format);
    va_list tmp_arg;

    va_copy(tmp_arg, arg);
    size_t len = vsnprintf(NULL, 0U, format, arg);
    msg = malloc(len + 1);

    vsprintf(msg, format, tmp_arg);
    va_end(tmp_arg);
    va_end(arg);

    printf("%s\n", msg);

    message_box(msg);

    free(msg);
}
#endif


int main(void) {

    #if NR
    get_message(
        "Hello, World!! %d\n"
        "This is a basic TCP server. %d\n"
        "Hope this program works as intended. %d",
        10, 100, 1000
    );

    printf("\n\n");
    #endif

    int socket_server_node = socket(AF_INET, SOCK_STREAM, 0);  // assigned an endpoint for server

    // assinging an IP and port to our server
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(server_addr.sin_zero), sizeof(server_addr.sin_zero));  // need to be zero

    // bind the server to the respective IP and Port
    int ret_val_bind = bind(socket_server_node, (struct sockaddr *)&server_addr, sizeof(server_addr));
    // making sure the server binds to the IP and Port
    if (ret_val_bind == -1) {
        perror("Bind failed\n");
        exit(-1);
    }
    else {
        printf("Bind successful. The return value is: %d\n", ret_val_bind);
        printf("Also the return value of socket is: %d\n", socket_server_node);
    }

    // listen for requests
    int ret_val_listen = listen(socket_server_node, 2);
    // making sure the server is listening
    if (ret_val_listen == -1) {
        perror("Listen failed.\n");
        exit(-1);
    }
    else
        printf("Listen succesfull. The return value is: %d\n", ret_val_listen);

    // logging client's IP and Port
    struct sockaddr_in client_addr;
    unsigned int size_client_addr = sizeof(client_addr);
    // accepting requests
    int ret_val_accept = accept(socket_server_node, (struct sockaddr *)&client_addr, &size_client_addr);
    // making sure that server accepts the connection request
    if (ret_val_accept == -1) {
        perror("Accept failed.\n");
        exit(-1);
    }
    else {
        printf("Accept successful. The return value is: %d\n", ret_val_accept);
        printf(
            "Now the information of client is as follows:\n"
            "sin_family: %d\n"
            "sin_port: %d\n"
            "sin_addr: %s\n"
            "sin_zero: %s\n",
            client_addr.sin_family, client_addr.sin_port, inet_ntoa(client_addr.sin_addr), client_addr.sin_zero
        );
    }

    char message[512] = "Hello, World!! This is a basic TCP server.";
    int client_socket = ret_val_accept;

    long int ret_val_send = send(client_socket, message, sizeof(message), 0);
    // checking the return value of send
    // The return value is just the size of the message buffer
    printf("The return value of send is: %ld\n", ret_val_send);

    // closing the connection
    close(socket_server_node);

    return 0;
}
