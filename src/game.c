#include"../include/game.h"

int kingincheck(Game* myGame, pieces*** team){
  if(team[0][4]->team == white){
    if(team[0][4]->Alive == 0){
      printf("Determined winner 1\n");
      myGame->winner = black;
      return 2;
    }
    else{
      return team[0][4]->inDanger;
    }
  }
  else{
    if(team[1][4]->Alive == 0){
      myGame->winner = white;
      printf("Determined winner 2\n");
      return 2;
    }
    else{
    return team[1][4]->inDanger;
  }
  }
}

void checkGameStatus(Game* myGame, pieces* piece){
  int status;
  if(piece->team == black){
    status = kingincheck(myGame,myGame->blackTeam);
    if(status == 1 && myGame->checkBlack == 1){
      myGame->winner = white;
      return;
    }
    status = kingincheck(myGame,myGame->whiteTeam);
    if(status == 1){
        myGame->checkWhite = 1;
      }
      if(status == 0){
        myGame->checkWhite = 0;
      }
    }
  else{
    status = kingincheck(myGame,myGame->whiteTeam);
    if(status == 1 && myGame->checkWhite == 1){
      myGame->winner = black;
      return;
    }
    status = kingincheck(myGame,myGame->blackTeam);
    if(status == 1){
        myGame->checkBlack = 1;
      }
      if(status == 0){
        myGame->checkBlack = 0;
      }
  }
}

int
move(Game* myGame, pieces* piece, board* location)
{
  board* oldlocation = piece->position;
  pieces* oldpiece = nullptr;
  int oldHasMoved = piece->hasMoved;
  if(location->piece != nullptr)
  {
      oldpiece = location -> piece;
      //remove the dead piece from the board
      location->piece->Alive = 0;
      location->piece->position = nullptr;

  }

    piece->position->piece = nullptr;
    location->piece = piece;
    piece->position = location;
    calculateWarScore(myGame);
    calculateGameMoves(myGame);
    piece->hasMoved = 1;

    checkGameStatus(myGame,piece);

    return 0;
}

void
printgame(Game* myGame){
  printboard(myGame->gameBoard);
}

int move_in_movelist(pieces* piece, int* x2, int* y2) {
    movelist* head = piece->moves;

    while(head!= nullptr){
        // if head moves match the location to move
        if (head->move->x == *x2 && head->move->y == *y2) {
            return 1;
        }
        head = head->nextMove;
    }
    return 0;
}


int move_piece(Game* myGame, int* x1, int* y1, int* x2, int* y2, teams* current_team) {
    // make sure the piece to move actually exists
    if (myGame->gameBoard[*x1][*y1]->piece != nullptr) {
        // only allow the current team to move
        if (myGame->gameBoard[*x1][*y1]->piece->team == *current_team) {
            // only allow a valid move to be made
            if (move_in_movelist(myGame->gameBoard[*x1][*y1]->piece, x2, y2)) {
                move(myGame, myGame->gameBoard[*x1][*y1]->piece, myGame->gameBoard[*x2][*y2]);
                //myGame->gameBoard[*x2][*y2]->piece->hasMoved = 1;
                printgame(myGame);

                // current team is now the opponent
                switch_current_team(current_team);
                return 0;
            }
            // otherwise, move is invalid
            else {
                // format red
                printf("\x1b[1m\x1b[38;5;196mError: Invalid move \x1b[0m\n");
                return -2;
            }
        }
        // attempt at moving other team piece, print an invalid message
        else {
            if (myGame->gameBoard[*x1][*y1]->piece->team == black) {
                // format orange
                printf("\x1b[1m\x1b[38;5;208mYou can only move a white piece \x1b[0m\n");

                // Note: return values continue from -2 from input.c: parse_input()
                return -3;
            }
            else {
                // format orange
                printf("\x1b[1m\x1b[38;5;208mYou can only move a black piece \x1b[0m\n");
                return -4;
            }
        }
    }
    else {
        // no piece at location to move
        // format red
        printf("\x1b[1m\x1b[38;5;196mError: there is no piece to move\x1b[0m\n");
        return -5;
    }
}

void switch_current_team(teams* current_team) {
    if (*current_team == black) {
        *current_team = white;
    }
    else {
        *current_team = black;
    }
}

void print_winning_team(Game* myGame) {
    if (myGame->winner == black) {
        // format it green
        printf("\n\x1b[1m\x1b[38;5;118m Black team wins! \x1b[0m\n");
    }
    else {
        printf("\n\x1b[1m\x1b[38;5;118m White team wins! \x1b[0m\n");
    }
}

void ai_move(teams* current_team, Game* myGame, int* x1, int* x2, int* y1, int* y2) {
    char* msg = malloc(sizeof(char) * 8);

    minimax *newMove;
    if (*current_team == white) {
        newMove = minORmax(myGame, myGame->whiteTeam);
    } else {
        newMove = minORmax(myGame, myGame->blackTeam);
    }
    *x1 = newMove->piece->position->x;
    *y1 = newMove->piece->position->y;
    *x2 = newMove->move->x;
    *y2 = newMove->move->y;

    format_out_message(msg, x1, x2, y1, y2);
    printf("\nAI moved from %c%c to %c%c\n", msg[0], msg[1], msg[3], msg[4]);
    //printf("(x1,y1)->(x2,y2) = (%d,%d)->(%d,%d)\n", *x1, *y1, *x2, *y2);
    move_piece(myGame, x1, y1, x2, y2, current_team);
    free(msg);
}