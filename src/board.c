#include"../include/board.h"

const int values[] = {0,1,5,3,3,9,10000};

void freeTeamMoves(pieces*** team){
  for(int i = 0; i < 2; i++)
  {
    for(int j = 0; j < rows; j++)
    {
      freePieceMoves(team[i][j]);
    }
  }
}

void calculateTeamMoves(board*** myBoard,pieces*** team){
  for(int i = 0; i < 2; i++)
  {
    for(int j = 0; j < rows; j++)
    {
      if(team[i][j]->Alive == 1)
      {
        calculatePieceMoves(myBoard,team[i][j]);
      }
    }
  }
}

void
calculateGameMoves(Game* myGame)
{
  freeTeamMoves(myGame->whiteTeam);
  freeTeamMoves(myGame->blackTeam);
  calculateTeamMoves(myGame->gameBoard,myGame->whiteTeam);
  calculateTeamMoves(myGame->gameBoard,myGame->blackTeam);

}

//TODO: include warscores
void
printboard(board*** myBoard)
{
  int bg_color;

  for(int i = 0; i < rows; i++){
    for(int j = 0; j < rows; j++){
      // logic to print an alternating background color for the chess board
      // using ANSI escape codes
      // go to http://www.lihaoyi.com/post/BuildyourownCommandLinewithANSIescapecodes.html
      // for a full list of color options available
      if (i % 2 == 0) {
        if (j % 2 == 0) {
          bg_color = 130; // 130 = dark brown
        }
        else {
          bg_color = 221; // 221 = tan color
        }
      }
      else {
        if (j % 2 == 0) {
          bg_color = 221;
        }
        else {
          bg_color = 130;
        }
      }

      // print each piece on the board with the selected bg color
      printpiece(myBoard[i][j]->piece, bg_color);
    }
    // x1b[1m         specifies bold text
    // x1b[38;5;195   specifies a white/very light blue color
    // x1b[0m         specifies to reset all formatting so that
    //                all subsequent text is in standard font
    //
    // all the formatting is concatenated into one long string
    printf("\x1b[1m\x1b[38;5;195m %d \x1b[0m\n", i);
  }
  printf("\x1b[1m\x1b[38;5;195m A  B  C  D  E  F  G  H \x1b[0m\n");
}


Game*
copyboard(Game* myGame)
{
  Game* newBoard = initBlankBoard();
  newBoard->whiteTeam = copyteam(myGame->whiteTeam);
  newBoard->blackTeam = copyteam(myGame->blackTeam);
  for(int i = 0; i < 2; i++)
  {
    for(int j = 0; j < rows; j++)
    {
      if(myGame->whiteTeam[i][j]->Alive == 1){
        newBoard->whiteTeam[i][j]->position = newBoard->gameBoard[myGame->whiteTeam[i][j]->position->x][myGame->whiteTeam[i][j]->position->y];
        newBoard->whiteTeam[i][j]->position->piece = newBoard->whiteTeam[i][j];
      }
      if(myGame->blackTeam[i][j]->Alive == 1){
        newBoard->blackTeam[i][j]->position = newBoard->gameBoard[myGame->blackTeam[i][j]->position->x][myGame->blackTeam[i][j]->position->y];
        newBoard->blackTeam[i][j]->position->piece = newBoard->blackTeam[i][j];
      }



    }
  }
  calculateGameMoves(newBoard);
  calculateWarScore(newBoard);
  return newBoard;

}

void
calculateWarScore(Game* myGame)
{
  //create to empty tempscores
  int tempScoreWhite = 0;
  int tempScoreBlack =0;

  //add for being alive
  for(int i = 0; i < 2; i++){
    for(int j = 0; j < rows; j++){
      if(myGame->whiteTeam[i][j]->Alive == 1){
        //add for being alive
        tempScoreWhite += values[myGame->whiteTeam[i][j]->type];
        //add for moving forward
        tempScoreWhite += myGame->whiteTeam[i][j]->position->x - 2 +
          values[myGame->whiteTeam[i][j]->type];
      }
      if(myGame->blackTeam[i][j]->Alive == 1){
        //add for being alive
        tempScoreBlack += values[myGame->blackTeam[i][j]->type];
        //add for moving forward
        tempScoreBlack += 6 - myGame->blackTeam[i][j]->position->x +
          values[myGame->blackTeam[i][j]->type];
      }
      //add for taking pieces
      if(myGame->whiteTeam[i][j]->Alive == 0){
        tempScoreBlack += values[myGame->whiteTeam[i][j]->type];
      }
      //add for taking pieces
      if(myGame->blackTeam[i][j]->Alive == 0){
        tempScoreWhite+= values[myGame->blackTeam[i][j]->type];
      }
      //add for puting pieces in Danger
      if(myGame->whiteTeam[i][j]->inDanger == 1){
        tempScoreBlack += values[myGame->whiteTeam[i][j]->type] / 2;
        tempScoreWhite += -1 * (values[myGame->whiteTeam[i][j]->type] /2);
      }
      //add for puting pieces in Danger
      if(myGame->blackTeam[i][j]->inDanger == 1){
        tempScoreWhite += values[myGame->blackTeam[i][j]->type] / 2;
        tempScoreBlack += -1 * (values[myGame->blackTeam[i][j]->type] /2);
      }
    }
  }

  //place the final values back into the myBoard pointer
  myGame->BlackWarScore = tempScoreBlack;
  myGame->WhiteWarScore = tempScoreWhite;
}


Game*
initStartBoard()
{
   Game* myGame = initBlankBoard();
   myGame->whiteTeam = initTeam(white);
   myGame->blackTeam = initTeam(black);

   for(int i = 0; i < 2; i++){
     for(int j = 0; j < rows; j++){
       myGame->gameBoard[i][j]->piece = myGame->whiteTeam[i][j];
       myGame->whiteTeam[i][j]->position = myGame->gameBoard[i][j];
     }
   }
   for(int i = 6; i < rows; i++){
     for(int j = 0; j < rows; j++){
       myGame->gameBoard[i][j]->piece = myGame->blackTeam[i-6][j];
       myGame->blackTeam[i-6][j]->position = myGame->gameBoard[i][j];
     }
   }
   calculateGameMoves(myGame);

   return myGame;
 }


 Game*
 initBlankBoard()
 {
   Game* myGame = allocateBoard(myGame);

   for(int i = 0; i < rows; i++){
     for(int j = 0; j < rows; j++){
       board* temp = (board*)malloc(sizeof(board));
       temp->piece = nullptr;
       temp->x = i;
       temp->y = j;
       myGame->gameBoard[i][j] = temp;
     }
   }

   return myGame;
 }


Game*
allocateBoard(Game* myBoard)
{
  myBoard = (Game*)malloc(sizeof(Game));
  myBoard->gameBoard = (board***)malloc(sizeof(board**) * rows);
  for(int i = 0; i < rows; i++){
    myBoard->gameBoard[i] = (board**)malloc(sizeof(board* ) * rows);
  }
  return myBoard;
}


void
freeboard(Game* myGame)
{
  freeTeamMoves(myGame->whiteTeam);
  freeTeamMoves(myGame->blackTeam);
  freeteam(myGame->whiteTeam);
  freeteam(myGame->whiteTeam);

  for(int i = 0; i < rows; i++)
  {
    for(int j = 0; j < rows; j++)
    {
      free(myGame->gameBoard[i][j]);
    }
    free(myGame->gameBoard[i]);
  }

  free(myGame);
}


void
printattack(pieces* attackedPiece, Game* myBoard, pieces* toMovePiece, int x,int y)
{
  printf("Attacked piece type == %d of team == %d which is now (dead/alive) == %d\n",attackedPiece->type,attackedPiece->team,attackedPiece->Alive);
}
