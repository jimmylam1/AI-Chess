#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8080
#define MSG_LEN 64

// initialize the server
void init_server(int* server, struct sockaddr_in* server_addr, int*opt);

// connect to a client
void connect_to_client(int* server, struct sockaddr_in* server_addr, int* addrlen, int* new_socket);

// get a message from the client
int get_message(int* new_socket, char* in_message);

// send a message to the client
int send_message(int* new_socket, char* out_message);
