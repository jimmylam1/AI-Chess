#ifndef PIECE_H
#define PIECE_H
#ifndef DEBUG
#define DEBUG 0
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Ability to use nullpty instead of NULL
#define nullptr (((void*) 0))

//quick way to reference the size of the board and number of overall pieces
static const int rows = 8;
static const int numPieces = 32;

//declarations of all structures and substructures
//to be implimented in their respective files
typedef struct myboard board;
typedef struct mymovelist movelist;
typedef struct mypieces pieces;
typedef struct mygame Game;

//easy way to reference piece types and teams
typedef enum {noteam, white, black} teams;
typedef enum {nopiece, pawn, rook, knight, bishop, queen, king} piecetypes;


//to be used in the in the gameboard of the gamestruct
//contains the current board posiiton (x,y)
typedef struct myboard{
  int x;
  int y;
  struct mypieces* piece;
} board;


//this will be a linked list of potential board locations
//that a piece can move to
typedef struct mymovelist{
  board* move;
  movelist* nextMove;
} movelist;

//the actual game piece
typedef struct mypieces{
    piecetypes type; //the type of piece
    teams team; //the team the piece belongs to
    int inDanger; //whether or not it can be attacked by another piece in its current location
    board* position; //current position on the gameboard
    int Alive; //whether it is alive (1) or dead (0)
    movelist* moves; //linked list of all potential moves
    int hasMoved; //0 if a piece hasn't moved yet, 1 if it has

} pieces;

void calculatePieceMoves(board*** myBoard,pieces* piece);

/*
*   FUNCTION: movePawn(board*** myBoard,pieces* piece)
*
*   DESCRIPTION: Not intended for direct use. Used by calculatePieceMoves.
*   determines all valid movies for the current piece
*
*   ARGUMENTS: Fully initialized piece and gameboard
*
*   RETURN: None
*
*   SIDE EFFECTS: The piece's movelist is updated with the valid moves
*
*/
void movePawn(board*** myBoard,pieces* piece);

/*
*   FUNCTION: moveRook(board*** myBoard,pieces* piece)
*
*   DESCRIPTION: Not intended for direct use. Used by calculatePieceMoves.
*   determines all valid movies for the current piece
*
*   ARGUMENTS: Fully initialized piece and gameboard
*
*   RETURN: None
*
*   SIDE EFFECTS: The piece's movelist is updated with the valid moves
*
*/
void moveRook(board*** myBoard,pieces* piece);

/*
*   FUNCTION: moveKnight(board*** myBoard,pieces* piece)
*
*   DESCRIPTION: Not intended for direct use. Used by calculatePieceMoves.
*   determines all valid movies for the current piece
*
*   ARGUMENTS: Fully initialized piece and gameboard
*
*   RETURN: None
*
*   SIDE EFFECTS: The piece's movelist is updated with the valid moves
*
*/
void moveKnight(board*** myBoard,pieces* piece);

/*
*   FUNCTION: moveBishop(board*** myBoard,pieces* piece)
*
*   DESCRIPTION: Not intended for direct use. Used by calculatePieceMoves.
*   determines all valid movies for the current piece
*
*   ARGUMENTS: Fully initialized piece and gameboard
*
*   RETURN: None
*
*   SIDE EFFECTS: The piece's movelist is updated with the valid moves
*
*/
void moveBishop(board*** myBoard,pieces* piece);

/*
*   FUNCTION: moveQueen(board*** myBoard,pieces* piece)
*
*   DESCRIPTION: Not intended for direct use. Used by calculatePieceMoves.
*   determines all valid movies for the current piece
*
*   ARGUMENTS: Fully initialized piece and gameboard
*
*   RETURN: None
*
*   SIDE EFFECTS: The piece's movelist is updated with the valid moves
*
*/
void moveQueen(board*** myBoard,pieces* piece);

/*
*   FUNCTION: moveKing(board*** myBoard,pieces* piece)
*
*   DESCRIPTION: Not intended for direct use. Used by calculatePieceMoves.
*   determines all valid movies for the current piece
*
*   ARGUMENTS: Fully initialized piece and gameboard
*
*   RETURN: None
*
*   SIDE EFFECTS: The piece's movelist is updated with the valid moves
*
*/
void moveKing(board*** myBoard,pieces* piece);

/*
*   FUNCTION: addmove(pieces* head, board* myBoard)
*
*   DESCRIPTION: Not intended for direct use. Used by various movepiece functions
*   ensures that the target location does not contain piece of the same team, then
*   adds that location to the piece movelist
*
*   ARGUMENTS: Fully initialized piece and gameboard
*
*   RETURN: None
*
*   SIDE EFFECTS: The piece's movelist is updated the new board location.
*   if that board location has an enemy piece, its inDanger value is updated
*
*/
void addmove(pieces* head, board* myBoard);

/*
*   FUNCTION: freePieceMoves(pieces* piece)
*
*   DESCRIPTION: Follows the linked list and frees allocated memory.
*
*   ARGUMENTS: Fully initialized piece
*
*   RETURN: None
*
*   SIDE EFFECTS: The piece's movelist is empied and inDanger is reset to 0
*
*/
void freePieceMoves(pieces* piece);


/*
*   FUNCTION: printpiece(pieces* piece)
*
*   DESCRIPTION: Not intended for direct use. Used by printboard to print the pieces
*
*   ARGUMENTS: Fully initialized piece*
*
*   RETURN: None
*
*   SIDE EFFECTS: Individual piece is printed according to type attribute
*
*/
void printpiece(pieces* piece, int bg_color);

/*
*   FUNCTION: copyteam(pieces*** team)
*
*   DESCRIPTION: Not intended for direct use.
*
*   ARGUMENTS: Fully initialized team
*
*   RETURN: a deep copy of the original team array
*
*   SIDE EFFECTS: new memory is allocated
*
*/
pieces*** copyteam(pieces*** team);

/*
*   FUNCTION: initTeam(teams color)
*
*   DESCRIPTION: Calls the appropriate functions to allocate and initialize a
*   team with the given color
*
*   ARGUMENTS: teams enum color
*
*   RETURN: a newly allocated team array with all pieces initialized, but not
*   placed anywhere on the board
*
*   SIDE EFFECTS: new memory is allocated. All pieces have default values
*
*/
pieces*** initTeam(teams color);

/*
*   FUNCTION: initpieces(pieces*** tempTeams,teams color)
*
*   DESCRIPTION: given an allocated teams array. The array is initialized
*   with all pieces in their correct positions
*
*   ARGUMENTS: teams enum color, allocated teams array
*
*   RETURN: a teams array with all pieces initialized
*
*   SIDE EFFECTS: new memory is allocated. All pieces have default values
*
*/
pieces*** initpieces(pieces*** tempTeams,teams color);

/*
*   FUNCTION: initBlankTeam()
*
*   DESCRIPTION: Allocates enough space for a 2d array of pointers to pieces
*
*   ARGUMENTS: None
*
*   RETURN: a fully allocated teams array
*
*   SIDE EFFECTS: new memory is allocated.
*
*/
pieces*** initBlankTeam();

/*
*   FUNCTION: freeteam(pieces*** team)
*
*   DESCRIPTION: frees all the space allocated to the teams array
*
*   ARGUMENTS: None
*
*   RETURN:None
*
*   SIDE EFFECTS: teams array memory is freed
*
*/
void freeteam(pieces*** team);

/*
*   FUNCTION: printmoves(pieces* piece)
*
*   DESCRIPTION: prints all possible move locations of the given piece
*
*   ARGUMENTS: fully initialized piece
*
*   RETURN:None
*
*   SIDE EFFECTS: representation of the pieces potential moves are printed
*
*/
void printmoves(pieces* piece);

#endif
