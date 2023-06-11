#include "../include/input.h"

int check_format(char *message) {
    // check if message is the right length
    if (strlen(message) != 6) {
        return 0;
    }
    // check if there is an expected space
    if (message[2] != ' ') {
        return 0;
    }
    // check if first and third characters are letters
    if (!isalpha(message[0]) || !isalpha(message[3])) {
        return 0;
    }
    // check if first and fourth characters are digits
    if (!isdigit(message[1]) || !isdigit(message[4])) {
        return 0;
    }
    return 1;
}

void convert(char* message) {
    message[0] = (message[0] - 'A') + '0';
    message[3] = (message[3] - 'A') + '0';
}

void transfer(char* message, int* x1, int* x2, int* y1, int* y2) {
    *y1 = message[0] - '0';
    *x1 = message[1] - '0';
    *y2 = message[3] - '0';
    *x2 = message[4] - '0';
}

int is_valid(int* x1, int* x2, int* y1, int* y2) {
    if (*x1 > 7 || *x2 > 7 || *y1 > 7 || *y2 > 7) {
        return 0;
    }
    return 1;
}



int parse_input(char* move_data, int* x1, int* x2, int* y1, int* y2) {
    int is_invalid = 0;

    // check if the move data is correctly formatted
    if (!check_format(move_data)) {
        // format red
        printf("\x1b[1m\x1b[38;5;196mError: Incorrect move format \x1b[0m\n");
        return -1;
    }
    else {
        // convert to numeric value as char
        move_data[0] = toupper(move_data[0]);
        move_data[3] = toupper(move_data[3]);
        convert(move_data);

        transfer(move_data, x1, x2, y1, y2);
        if (!is_valid(x1, x2, y1, y2)) {
            is_invalid = 1;
        }

        if (is_invalid) {
            // format red
            printf("\x1b[1m\x1b[38;5;196mError: Invalid move \x1b[0m\n");
            return -2;
        }
        return 0;
    }

}

void get_first_move_team(teams* current_team) {
    char response;

    do {
        printf("\nWhich team do you want to be? (b/w): ");
        response = getchar();

        // remove newline character from the input stream
        getchar();

        if (response != 'b' && response != 'w') {
            // format orange
            printf("\n\x1b[1m\x1b[38;5;208mYou must enter either 'b' or 'w'\x1b[0m\n");
        }
        else {
            printf("\n");
        }

    } while (response != 'b' && response != 'w');

    if (response == 'b') {
        *current_team = black;
    }
    else {
        *current_team = white;
    }
}

void transfer_error_message(char* dest, int return_val) {
    // the additional characters are for formatting purposes
    // see the function printpiece() in piece.c for more description (~line 300)
    if (return_val == -1) {
        strcpy(dest, "\x1b[1m\x1b[38;5;196mError: Incorrect move format \x1b[0m\n");
    }
    else if (return_val == -2) {
        strcpy(dest, "\x1b[1m\x1b[38;5;196mError: Invalid move \x1b[0m\n");
    }
    else if (return_val == -3) {
        strcpy(dest, "\x1b[1m\x1b[38;5;208mYou can only move a white piece \x1b[0m\n");
    }
    else if (return_val == -4) {
        strcpy(dest, "\x1b[1m\x1b[38;5;208mYou can only move a black piece \x1b[0m\n");
    }
    else if (return_val == -5) {
        strcpy(dest, "\x1b[1m\x1b[38;5;196mError: there is no piece to move\x1b[0m\n");
    }
}

void convert_out_message(char* out_message) {
    out_message[0] = out_message[0] - '0' + 'A';
    out_message[3] = out_message[3] - '0' + 'A';
}

void get_input_mode(int* input_mode, int* ai, int argc, char**argv) {
    if (argc == 1) {
        // ran using ./chess so use stdin for input (default)
        *input_mode = 0;
    }
    else {
        // check if user wants to run with a client
        // run as ./chess -c       to connect to a client
        for (int i = 1; i < argc; i++) {
            // if -c flag is set
            if (argv[i][0] == '-' && argv[i][1] == 'c') {
                *input_mode = 1;
            }
            // if -ai flag is set
            else if (argv[i][0] == '-' && argv[i][1] == 'a' && argv[i][2] == 'i') {
                *ai = 1;
            }
        }
    }
}

void move_piece_from_input(char* message, Game* myGame, teams* current_team, int* x1, int* x2, int* y1, int* y2) {
    int result;
    do {
        printf("\nEnter move: ");
        fgets(message, MSG_LEN, stdin);
        result = parse_input(message, x1, x2, y1, y2);
        if (result == 0) {
            result = move_piece(myGame, x1, y1, x2, y2, current_team);
        }
    } while (result != 0);
}

int get_client_move(int* new_socket, char* in_message, Game* myGame, teams* current_team, int* x1, int* x2, int* y1, int* y2) {
    int return_val;
    // read in the message from the client
    printf("Waiting for a response...\n");
    get_message(new_socket, in_message);

    // optional: print the move of the client
    printf("%s", in_message);

    // parse the input move data from the client
    // and move the piece if it is valid
    return_val = parse_input(in_message, x1, x2, y1, y2);
    if (return_val == 0) {
        return_val = move_piece(myGame, x1, y1, x2, y2, current_team);
    }

    if (in_message[0] == 'x') {
        // return a largish negative number
        return_val = -10;
    }
    return return_val;
}

void format_out_message(char* out_message, int* x1, int* x2, int* y1, int* y2) {
    out_message[0] = *y1 + 'A';
    out_message[1] = *x1 + '0';
    out_message[2] = ' ';
    out_message[3] = *y2 + 'A';
    out_message[4] = *x2 + '0';
    out_message[5] = '\n';
    out_message[6] = '\0';
}
