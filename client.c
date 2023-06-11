#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8080
#define MSG_LEN 64
#define ADDRESS "127.0.0.1" // "127.0.0.1" for localhost

// function headers to stop gcc from complaining
int inet_pton(int af, const char *src, void *dst);
size_t read(int fd, void *buf, size_t count);

void init_client(int* client, struct sockaddr_in* server_addr) {
    // Creating socket file descriptor
    *client = socket(AF_INET, SOCK_STREAM, 0);

    if (*client < 0) {
        printf("Error creating client socket\n");
        return;
    }

    server_addr->sin_family = AF_INET;
    server_addr->sin_addr.s_addr = INADDR_ANY;
    server_addr->sin_port = htons(PORT);

    // Convert IP address from text to binary
    int inet = inet_pton(AF_INET, ADDRESS, &server_addr->sin_addr);
    if (inet <= 0)
    {
        printf("Error with converting IP address\n");
        return;
    }
}

int connect_to_server(int* client, struct sockaddr_in* server_addr, int size) {
    int val = connect(*client, (struct sockaddr *)server_addr, size);
    if (val < 0)
    {
        printf("\n\x1b[1m\x1b[31mERROR: Connection Failed\x1b[0m\n");
        printf("Make sure the IP address matches the server's (use ifconfig to check)\n");
        printf("If needed, change the IP address macro in client.c\n");
        printf("Note: this will not connect if the server is not running\n");
        return 0;
    }

    // format green
    printf("\n\x1b[1m\x1b[38;5;118mConnected to the server! \x1b[0m\n");
    return 1;
}

int main(int argc, char const *argv[])
{
    int client;
    struct sockaddr_in server_addr;

    char* first_team = malloc(sizeof(char) * MSG_LEN);
    char* out_message = malloc(sizeof(char) * MSG_LEN);
    char* in_message = malloc(sizeof(char) * MSG_LEN);

    // initialize the client
    init_client(&client, &server_addr);

    // connect to the server
    if (connect_to_server(&client, &server_addr, sizeof(server_addr)) == 0) {
        return -1;
    }

    // figure out which team the client is
    read(client, first_team, MSG_LEN);

    if (first_team[0] == 'w') {
        do {
            // get input message
            printf("Enter move: ");
            fgets(out_message, MSG_LEN, stdin);

            send(client, out_message, strlen(out_message), 0);

            if (out_message[0] == 'x') {
                break;
            }
            // clear input message
            for (int i = 0; i < MSG_LEN; i++) {
                in_message[i] = '\0';
            }

            // read move from server
            printf("Waiting for a response\n\n");
            read(client, in_message, MSG_LEN);
            printf("%s", in_message);

        } while (in_message[0] != 'x');
    }
    // else, first_team[0] == 'b'
    else {
        do {
            // clear input message
            for (int i = 0; i < MSG_LEN; i++) {
                in_message[i] = '\0';
            }

            // read move from server
            printf("Waiting for a response\n\n");
            read(client, in_message, MSG_LEN);
            printf("%s", in_message);

            // get input message
            printf("Enter move: ");
            fgets(out_message, MSG_LEN, stdin);
            send(client, out_message, strlen(out_message), 0);

            if (out_message[0] == 'x') {
                break;
            }
        } while (in_message[0] != 'x');
    }

    return 0;
}


