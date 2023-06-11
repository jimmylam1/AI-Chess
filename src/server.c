#include "../include/server.h"

void init_server(int* server, struct sockaddr_in* server_addr, int*opt) {
    // Creating socket file descriptor
    // int socket(int *domain, int type, int protocol)
    *server = socket(AF_INET, SOCK_STREAM, 0);

    // setsockopt allows for reuse of ports. Otherwise, the server may get
    // a binding error when rerunning.
    if (setsockopt(*server, SOL_SOCKET, SO_REUSEADDR, (char*)opt, sizeof(*opt)) < 0) {
        printf("setsockopt(SO_REUSEADDR) failed");
    }

    if (*server < 0) {
        printf("Error creating server socket\n");
        return;
    }

    server_addr->sin_family = AF_INET;
    server_addr->sin_addr.s_addr = INADDR_ANY;
    server_addr->sin_port = htons(PORT);

    // int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    if (bind(*server, (struct sockaddr *)server_addr, sizeof(*server_addr)) < 0) {
        printf("Error binding server\n");
        return;
    }
}

void connect_to_client(int* server, struct sockaddr_in* server_addr, int* addrlen, int* new_socket) {

    printf("\nWaiting for a connection...\n");

    // int listen(int sockfd, int backlog)
    // backlog is the maximum number of pending connections allowed
    if (listen(*server, 1) < 0) {
        printf("Error in listening\n");
        return;
    }

    // int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
    *new_socket = accept(*server, (struct sockaddr *)server_addr, (unsigned int*)addrlen);

    if (*new_socket < 0) {
        printf("Error accepting socket\n");
        return;
    }
    // format green
    printf("\n\x1b[1m\x1b[38;5;118mA client has connected! \x1b[0m\n");
}

int get_message(int* new_socket, char* in_message) {
    // clear the incoming message string
    for (int i = 0; i < MSG_LEN; i++) {
        in_message[i] = '\0';
    }

    // read the incoming message
    read(*new_socket, in_message, MSG_LEN);

    if (in_message[0] == 'x') {
        return -1;
    }
    return 0;
}

int send_message(int* new_socket, char* out_message) {

    send(*new_socket, out_message, strlen(out_message), 0);

    if (out_message[0] == 'x') {
        return -1;
    }
    return 0;
}

