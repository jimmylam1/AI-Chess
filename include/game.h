#ifndef GAME_H
#define GAME_H
#include "board.h"
#include "test.h"
#include "server.h"
#include "input.h"


/*
*   The board struct contains all necessary information about the current
*   game board and allows for easily passing this information around and cloning
*/
typedef struct mygame{
    //Each "team" or "side" has their own 2D array of pointers that point to
    //individual pieces structures. Each "team" array has dimensions 2 * rows
    pieces*** whiteTeam;
    pieces*** blackTeam;

    //The game board is another 2D array of pointers to pieces struct
    //but is instead of size rows * rows and points to all pieces in the game
    //instead of just the pieces of a specific team.
    //TODO: Intended to isolate teams from accessing information about another players potential moves
    board*** gameBoard;

    //Each team has a "Warscore" that is equivalent to their sum total of piecetypes
    //still in play + the distance they've moved towards the oposing side
    //TODO: Warscore needs to include the total number of oposing pieces "inDanger"
    double WhiteWarScore;
    double BlackWarScore;

    //quick way to reference if the given team is in check
    int checkWhite;
    int checkBlack;

    //used for game termination. While empty the came continues
    teams winner;

} Game;


/*
*   FUNCTION: move(board* myBoard, pieces* toMovePiece, board* location);
*
*   DESCRIPTION: Moves a pieces* to position location*
*
*   ARGUMENTS: board* and all substructures must be initialized.
*   pieces* is the piece that you want to move or attack with which can be accessed
*   by whiteTeam[i][j] or blackTeam[i][j] or gameBoard[i][j]
*
*   RETURN: 0 if the move was unsuccessful, 1 if it was only a move, 2 if it was an attack
*
*   SIDE EFFECTS: Gameboard[x][y] now points to "toMovePiece". If it was an
*   attack, the defending piece is removed from the board with attribute alive = 0.
*   WhiteWarScore & BlackWarScore values are updated.
*
*/
int move(Game* myBoard, pieces* piece, board* location);

/*
*   FUNCTION: printgame(Game* myGame)
*
*   DESCRIPTION: Prints a visual representation of the current Game
*
*   ARGUMENTS: Fully initialized Game
*
*   RETURN: None
*
*   SIDE EFFECTS: Visual representation of the Game is printed to the terminal
*
*/
void printgame(Game* myGame);

// move piece form (x1, y1) to (x2, y2)
// also prints the board if a piece moves
int move_piece(Game* myGame, int* x1, int* y1, int* x2, int* y2, teams* current_team);

// switches the current team
void switch_current_team(teams* current_team);

// make sure the move is a possible move
int move_in_movelist(pieces* piece, int* x2, int* y2);

//to determine if games are won
void checkGameStatus(Game* myGame, pieces* piece);

/*
*   FUNCTION: kingincheck(Game* myGame, pieces*** team)
*
*   DESCRIPTION: returns a 1 if the given team's king is in check
*
*   ARGUMENTS: Fully initialized Game
*
*   RETURN: None
*
*   SIDE EFFECTS: The game's attribute of "checkWhite" or "checkBlack" may be
*   altered
*
*/
int kingincheck(Game* myGame, pieces*** team);

// print the winning team
void print_winning_team(Game* myGame);

// the main ai driver
// minimax is called and the move is automatically executed on the chess board
void ai_move(teams* current_team, Game* myGame, int* x1, int* x2, int* y1, int* y2);

#endif
