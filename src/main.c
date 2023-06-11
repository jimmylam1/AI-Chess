#include <stdio.h>
#include <stdlib.h>
#include "../include/game.h"

int main(int argc, char **argv)
{
    int input_mode = 0, ai = 0, return_val, current_move = 0;
    char* in_message = malloc(sizeof(char) * MSG_LEN);
    char* out_message = malloc(sizeof(char) * MSG_LEN);
    teams* current_team = malloc(sizeof(teams));
    int* x1 = malloc(sizeof(int));
    int* x2 = malloc(sizeof(int));
    int* y1 = malloc(sizeof(int));
    int* y2 = malloc(sizeof(int));

    #if DEBUG
        test();
        testDeepCopy();
        testlinkedlist();
        testGeneratedMoves();
        testminimax();
    #endif

    get_input_mode(&input_mode, &ai, argc, argv);
    printf("Note: use -c to run with a remote client, -ai to use ai\n");
    printf("STATUS: input_mode=%d ai=%d\n", input_mode, ai);

    Game* myGame = initStartBoard();
    get_first_move_team(current_team);
    printgame(myGame);
    // x1b[1m    for bold text
    // x1b[0m    to clear formatting
    printf("\n\x1b[1mTo move a piece, type (for example) 'A1 A2'\n");
    printf("in order to move the piece from location A1 to A2\x1b[0m\n");

    if (input_mode == 0) {
        // ----------------------- use stdin for input -----------------------
        if (ai) {
            // play against ai
            do {
                if (current_move % 2 == 0) {
                    move_piece_from_input(in_message, myGame, current_team, x1, x2, y1, y2);
                } else {
                    ai_move(current_team, myGame, x1, x2, y1, y2);
                }
                current_move++;
            } while (myGame->winner == 0);
            print_winning_team(myGame);
        }
        else {
            // no ai
            do {
                move_piece_from_input(in_message, myGame, current_team, x1, x2, y1, y2);
            } while (myGame->winner == 0);
            print_winning_team(myGame);
        }
    }
    else if (input_mode == 1) {
        // ----------------------- use remote client for input -----------------------
        //           Note: the computer running this program is the server
        int server, new_socket, opt = 1;
        struct sockaddr_in server_addr;
        int addrlen = sizeof(server_addr);

        // initialize the server
        init_server(&server, &server_addr, &opt);

        // connect to a client
        connect_to_client(&server, &server_addr, &addrlen, &new_socket);

        if (*current_team == black) {
            // change the current team because the client must be white, and white goes first
            *current_team = white;
            send_message(&new_socket, "w");
            do {
                // get moves from the client and move the piece
                return_val = get_client_move(&new_socket, in_message, myGame, current_team, x1, x2, y1, y2);
                if (return_val == -10) {
                    return -1;
                }
                // if the client sent a valid move, send a move from the server back
                if (return_val == 0) {
                    if (ai) {
                        ai_move(current_team, myGame, x1, x2, y1, y2);
                        format_out_message(out_message, x1, x2, y1, y2);
                    }
                    else {
                        // get user input for the move
                        move_piece_from_input(out_message, myGame, current_team, x1, x2, y1, y2);
                        format_out_message(out_message, x1, x2, y1, y2);
                    }
                }
                // otherwise, copy error message to out_message due to the client's invalid move
                else {
                    transfer_error_message(out_message, return_val);
                }

                // send the move or error message back to the client
                send_message(&new_socket, out_message);
                if (out_message[0] == 'x') {
                    return -1;
                }

            } while (myGame->winner == 0);
            // print winning team
            print_winning_team(myGame);
            return 0;
        }
        else {
            // server is white, server goes first
            send_message(&new_socket, "b");
            do {
                // get move from server side
                if (ai) {
                    ai_move(current_team, myGame, x1, x2, y1, y2);
                    format_out_message(out_message, x1, x2, y1, y2);
                } else {
                    // get user input for the move
                    move_piece_from_input(out_message, myGame, current_team, x1, x2, y1, y2);
                    format_out_message(out_message, x1, x2, y1, y2);
                }
                send_message(&new_socket, out_message);

                // get move from client
                do {
                    return_val = get_client_move(&new_socket, in_message, myGame, current_team, x1, x2, y1, y2);
                    if (return_val == -10) {
                        return -1;
                    }
                    // if the client sent a valid move, send a move from the server back
                    // otherwise, copy error message to out_message due to the client's invalid move
                    if (return_val != 0) {
                        transfer_error_message(out_message, return_val);
                        send_message(&new_socket, out_message);
                    }
                    if (out_message[0] == 'x') {
                        return -1;
                    }
                } while (return_val != 0);
            } while (myGame->winner == 0);
            // print winning team
            print_winning_team(myGame);
            return 0;
        }
    }

    // free memory
    free(in_message);
    free(out_message);
    free(current_team);
    free(x1);
    free(x2);
    free(y1);
    free(y2);

    return 0;

}
