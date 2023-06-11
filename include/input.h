#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "server.h"
#include "piece.h"
#include "game.h"

// make sure the input message is in the correct form (doesn't check
// to see if the move is valid or not)
int check_format(char* message);

// convert first and fourth character from uppercase to numeric value
void convert(char* message);

// parses input, checks message is valid, and converts necessary characters
int parse_input(char* message, int* x1, int* x2, int* y1, int* y2);

// transfer each character from message into corresponding xy values
void transfer(char* message, int* x1, int* x2, int* y1, int* y2);

// checks to make sure input is a valid move
int is_valid(int* x1, int* x2, int* y1, int* y2);

// figure out which team is moving first
void get_first_move_team(teams* current_team);

// transfers an error message to dest
// uses the return value as indication of which message to print
void transfer_error_message(char* dest, int return_val);

// convert numeric moves from parsing back into proper formatting
void convert_out_message(char* out_message);

// decide on if input should be stdin or with a client
void get_input_mode(int* input_mode, int* ai, int argc, char** argv);

// get user input for their move and parses it. If the move is
// valid, move the piece. Otherwise, continue to get input
// until a valid move is received
void move_piece_from_input(char* in_message, Game* myGame, teams* current_team, int* x1, int* x2, int* y1, int* y2);

// get a move input from the client
int get_client_move(int* new_socket, char* in_message, Game* myGame, teams* current_team, int* x1, int* x2, int* y1, int* y2);

// formats the output message from something like '34 35' to 'C4 C5'
void format_out_message(char* out_message, int* x1, int* x2, int* y1, int* y2);