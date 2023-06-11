#ifndef BOARD_H
#define BOARD_H

#include "piece.h"
#include "game.h"


/*
*   FUNCTION: calculateGameMoves(Game* myGame)
*
*   DESCRIPTION: Calculates all possible for each piece in the game
*
*   ARGUMENTS: fully initialized Game
*
*   RETURN: None
*
*   SIDE EFFECTS: The linked lists associated with each piece is updated
*
*/
void calculateGameMoves(Game* myGame);

/*
*   FUNCTION: calculateTeamMoves(board*** myBoard,pieces*** team)
*
*   DESCRIPTION: Not intended for direct use. Used by calculateGameMoves.
*   Calculates all possible movies for the given team
*
*   ARGUMENTS: fully initialized gameboard and team
*
*   RETURN: None
*
*   SIDE EFFECTS: The linked lists associated with each piece in team is updated
*
*/
void calculateTeamMoves(board*** myBoard,pieces*** team);

/*
*   FUNCTION: freeTeamMoves(pieces*** team);
*
*   DESCRIPTION: Not intended for direct use. Used by calculateGameMoves.
*   frees the heap memory allocated for the linked lists used for movelist
*
*   ARGUMENTS: fully initialized team
*
*   RETURN: None
*
*   SIDE EFFECTS: The linked lists associated with each piece in team is freed
*
*/
void freeTeamMoves(pieces*** team);

/*
*   FUNCTION: calculateWarScore(board* myBoard)
*
*   DESCRIPTION: Calculates/Updates the warscore for the given board based on
*   the warscore parameters
*
*   ARGUMENTS: board* and all substructures must be initialized
*
*   RETURN: No RETURN
*
*   SIDE EFFECTS: WhiteWarScore & BlackWarScore values are updated
*
*/
void calculateWarScore(Game* myBoard);

/*
*   FUNCTION: allocateBoard(board* myBoard)
*
*   DESCRIPTION: Not intended for direct use. Takes in an unallocated board*
*   and allocates sufficient memory on the heap
*
*   ARGUMENTS: uninitialized board*
*
*   RETURN: board* address of the allocated board on the heap
*
*   SIDE EFFECTS: None
*
*/
Game* allocateBoard(Game* myBoard);

/*
*   FUNCTION: initBlankBoard()
*
*   DESCRIPTION: Not intended for direct use. Initializes a blank gameBoard
*   of rows * rows grid to nullptr. Used by initStartBoard and copyboard()
*
*   ARGUMENTS: None
*
*   RETURN: board* address of the initialized gameBoard
*
*   SIDE EFFECTS: None
*
*/
Game* initBlankBoard();

/*
*   FUNCTION: initStartBoard()
*
*   DESCRIPTION: Allocates and Initializes a new game with pieces in default position
*
*   ARGUMENTS: None
*
*   RETURN: board* to new Game
*
*   SIDE EFFECTS: None
*
*/
Game* initStartBoard();

/*
*   FUNCTION: copyboard(board* myboard)
*
*   DESCRIPTION: Creates a "deep copy" of the given board*
*
*   ARGUMENTS: fully initialized Game struct
*
*   RETURN: board* to the newly created copy
*
*   SIDE EFFECTS: None
*
*/
Game* copyboard(Game* myboard);

/*
*   FUNCTION: freeboard(board* myboard)
*
*   DESCRIPTION: frees the heap memory of an initialized Game
*
*   ARGUMENTS: fully initialized Game struct
*
*   RETURN: None
*
*   SIDE EFFECTS: The heap memory of the Game struct and all substructures are freed
*
*/
void freeboard(Game* myBoard);

/*
*   FUNCTION: printboard()
*
*   DESCRIPTION: Prints a visual representation of the current gameBoard
*
*   ARGUMENTS: Fully initialized Game
*
*   RETURN: None
*
*   SIDE EFFECTS: Visual representation of the Game is printed to the terminal
*
*/
void printboard(board*** myBoard);

//test function
void printattack(pieces* attackedPiece, Game* myBoard, pieces* toMovePiece, int x,int y);

#endif
