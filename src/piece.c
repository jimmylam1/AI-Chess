#include"../include/piece.h"

void addmove(pieces* piece, board* myBoard){
  if(myBoard->piece != nullptr){
    if(myBoard->piece->team == piece->team){
      return;
    }
    else{
      myBoard->piece->inDanger = 1;
    }
  }

  if(piece->moves == nullptr){
    piece->moves = (movelist*)malloc(sizeof(movelist));
    piece->moves->move = myBoard;
    piece->moves->nextMove = nullptr;
  }
  else{
    movelist* head = piece->moves;
    movelist* temp;
    while(head != nullptr){
      temp = head;
      head = head->nextMove;
    }
    temp->nextMove = (movelist*)malloc(sizeof(movelist));
    head = temp->nextMove;
    head->move = myBoard;
    head->nextMove = nullptr;
  }
  }


void
freePieceMoves(pieces* piece)
{
  piece->inDanger = 0;
  if(piece->moves == nullptr){
    return;
  }
  else{
    movelist* head = piece->moves;
    movelist* temp;
    while(head != nullptr){
      temp = head;
      head = head->nextMove;
      free(temp);
    }
  }
  piece->moves = nullptr;

}

void
calculatePieceMoves(board*** myBoard,pieces* piece){
  if(piece->type == pawn){
    movePawn(myBoard,piece);
  }
   else if(piece->type == rook){
       moveRook(myBoard,piece);
     }
  else if(piece->type == knight){
      moveKnight(myBoard,piece);
    }
  else if(piece->type == bishop){
      moveBishop(myBoard,piece);
    }
  else if(piece->type == queen){
      moveQueen(myBoard,piece);
  }
  else if(piece->type == king){
    moveKing(myBoard,piece);
  }
}

void movePawn(board*** myBoard,pieces* piece){
  int x = piece->position->x;
  int y = piece->position->y;
  int x2;
  if(piece->team == white){
    x++;
    x2 = x + 1;
  }
  else if (piece->team == black){
    x--;
    x2 = x - 1;

  }
  if(x < 0 || x >= rows){
    return;
  }
  if(myBoard[x][y]->piece == nullptr)
  {
      addmove(piece,myBoard[x][y]);
  }
  if(y - 1 >= 0 && myBoard[x][y - 1]->piece != nullptr)
  {
      addmove(piece,myBoard[x][y - 1]);
  }
  if(y + 1 < rows && myBoard[x][y + 1]->piece != nullptr)
  {
      addmove(piece,myBoard[x][y + 1]);
  }
  if(x2 < 0 || x >= rows){
    return;
  }
  // move two spaces if pawn hasn't moved yet
  if(myBoard[x2][y]->piece == nullptr && piece->hasMoved == 0)
  {
    addmove(piece,myBoard[x2][y]);
  }


}


 void moveRook(board*** myBoard,pieces* piece){
   int x = piece->position->x;
   int y = piece->position->y;

   //calculate "up"
   while(x + 1 < rows){
     x = x + 1;
     if(myBoard[x][y]->piece == nullptr){
       addmove(piece,myBoard[x][y]);
     }
     else if(myBoard[x][y]->piece != nullptr){
       addmove(piece,myBoard[x][y]);
       break;
     }
   }

   //calculate down
   x = piece->position->x;
   y = piece->position->y;

   while(x - 1 >= 0){
     x = x - 1;
     if(myBoard[x][y]->piece == nullptr){
       addmove(piece,myBoard[x][y]);
     }
     else if(myBoard[x][y]->piece != nullptr){
       addmove(piece,myBoard[x][y]);
       break;
     }
   }

   //calculate right
   x = piece->position->x;
   y = piece->position->y;

   while(y + 1 < rows){
     y = y + 1;
     if(myBoard[x][y]->piece == nullptr){
       addmove(piece,myBoard[x][y]);
     }
     else if(myBoard[x][y]->piece != nullptr){
       addmove(piece,myBoard[x][y]);
       break;
     }
   }

   //calculate left
   x = piece->position->x;
   y = piece->position->y;

   while(y - 1 >= 0){
     y = y - 1;
     if(myBoard[x][y]->piece == nullptr){
       addmove(piece,myBoard[x][y]);
     }
     else if(myBoard[x][y]->piece != nullptr){
       addmove(piece,myBoard[x][y]);
       break;
     }
   }
 }


void moveKnight(board*** myBoard,pieces* piece){
  int x = piece->position->x;
  int y = piece->position->y;

  //calculate one half
  if(x - 1 >= 0){
    if(y - 2 >= 0){
      addmove(piece, myBoard[x - 1][y - 2]);
    }
    if(y + 2 < rows){
      addmove(piece, myBoard[x - 1][y + 2]);
    }
    if(x - 2 >= 0){
      if(y - 1 >= 0){
        addmove(piece,myBoard[x - 2][y - 1]);
      }
      if(y + 1 < rows){
        addmove(piece,myBoard[x - 2][y + 1]);
      }
    }
  }

  //calculate second half
  if(x + 1 < rows){
    if(y - 2 >= 0){
      addmove(piece, myBoard[x + 1][y - 2]);
    }
    if(y + 2 < rows){
      addmove(piece, myBoard[x + 1][y + 2]);
    }
    if(x + 2 < rows){
      if(y - 1 >= 0){
        addmove(piece,myBoard[x + 2][y - 1]);
      }
      if(y + 1 < rows){
        addmove(piece,myBoard[x + 2][y + 1]);
      }
    }
  }

}

void moveBishop(board*** myBoard,pieces* piece){
  int xoriginal = piece->position->x;
  int yOriginal = piece->position->y;
  int x;
  int y;


  //down and to the right
  x = xoriginal + 1;
  y = yOriginal + 1;
  while(x < rows && y < rows){
    if(myBoard[x][y]->piece == nullptr){
      addmove(piece,myBoard[x][y]);
    }
    else{
      addmove(piece,myBoard[x][y]);
      break;
    }
    x++;
    y++;
  }

  //up and to the right
  x = xoriginal - 1;
  y = yOriginal + 1;
  while(x >= 0 && y < rows){
    if(myBoard[x][y]->piece == nullptr){
      addmove(piece,myBoard[x][y]);
    }
    else{
        addmove(piece,myBoard[x][y]);
        break;
  }
  x--;
  y++;
  }

  //up and to the left
  x = xoriginal - 1;
  y = yOriginal - 1;
  while(x >= 0 && y >= 0){
    if(myBoard[x][y]->piece == nullptr){
      addmove(piece,myBoard[x][y]);
    }
    else{
        addmove(piece,myBoard[x][y]);
    break;
  }
  x--;
  y--;
  }

  //down and to the left
  x = xoriginal + 1;
  y = yOriginal - 1;
  while(x < rows && y >= 0){
    if(myBoard[x][y]->piece == nullptr){
      addmove(piece,myBoard[x][y]);
    }
    else{
      addmove(piece,myBoard[x][y]);
      break;
    }
  x++;
  y--;
  }
}


void moveQueen(board*** myBoard,pieces* piece){
  moveRook(myBoard,piece);
  moveBishop(myBoard,piece);
}

void moveKing(board*** myBoard,pieces* piece){
  int x = piece->position->x;
  int y = piece->position->y;
  for(int i = x-1; i <= x+1; i++){
    for(int j = y-1; j <= y+1; j++){
        if(i== x && j==y){
          //skip
        }
        else if (i >= 0 && i < rows && j >= 0 && j < rows){
            addmove(piece,myBoard[i][j]);
        }
    }
  }
}


void
printpiece(pieces* piece, int bg_color)
{
  char letter;
  int letter_color = 15; // 15 = white

  if(piece == nullptr) {
    letter = ' ';
  }
  else if(piece->type == pawn) {
    letter = 'P';
  }
  else if(piece->type == rook){
    letter = 'R';
  }
  else if(piece->type == knight){
    letter = 'N';
  }
  else if(piece->type == bishop){
    letter = 'B';
  }
  else if(piece->type == queen){
    letter = 'Q';
  }
  else if(piece->type == king){
    letter = 'K';
  }

  if (piece != nullptr && piece->team == black) {
    letter_color = 232; // 232 = black
  }
  // formatting involves:
  // x1b[48;5;%dm   specifies the background color
  // x1b[1m         specifies bold text
  // x1b[38;5;%dm   specifies the letter color for the team (black or white)
  // x1b[0m         specifies to reset all formatting so that
  //                all subsequent text is in standard font
  //
  // all the formatting is concatenated into one long string
  printf("\x1b[48;5;%dm\x1b[1m\x1b[38;5;%dm %c \x1b[0m", bg_color, letter_color, letter);
}


pieces***
copyteam(pieces*** team)
{
  pieces*** newTeam = initBlankTeam();
  for(int i = 0; i < 2; i++)
  {
    for(int j = 0; j < rows; j++ )
    {
      newTeam[i][j]->type = team[i][j]->type;
      newTeam[i][j]->team = team[i][j]->team;
      newTeam[i][j]->inDanger = team[i][j]->inDanger;
      newTeam[i][j]->Alive = team[i][j]->Alive;
      newTeam[i][j]->hasMoved = team[i][j]->hasMoved;
    }
  }
  return newTeam;
}

pieces***
initpieces(pieces*** tempTeams,teams color)
{
  if(color == black)
  {
    for(int i = 0; i < 2; i++)
    {
      for(int j = 0; j < rows; j++)
      {
        pieces* temp = (pieces*)malloc(sizeof(pieces));
        temp->team = color;
        temp->inDanger = 0;
        temp->Alive = 1;
        temp->hasMoved = 0;

        if(i == 0)
        {
          temp->type = pawn;
          tempTeams[i][j] = temp;
        }

        else if(i == 1)
        {
          if(j==0 || j == 7)
          {
            temp->type = rook;
            tempTeams[i][j] = temp;
          }
          else if(j==1 || j == 6)
          {
            temp->type = knight;
            tempTeams[i][j] = temp;
          }
          else if(j==2 || j == 5)
          {
            temp->type = bishop;
            tempTeams[i][j] = temp;
          }
          else if(j == 3)
          {
            temp->type = queen;
            tempTeams[i][j] = temp;
          }
          else if(j == 4)
          {
            temp->type = king;
            tempTeams[i][j] = temp;
          }
        }
      }
    }
  }

  else if(color == white)
  {
    for(int i = 0; i < 2; i++)
    {
      for(int j = 0; j < rows; j++)
      {
        pieces* temp = (pieces*)malloc(sizeof(pieces));
        temp->team = color;
        temp->inDanger = 0;
        temp->Alive = 1;
        temp->hasMoved = 0;

        if(i == 1)
        {
          temp->type = pawn;
          tempTeams[i][j] = temp;
        }
        else if(i == 0)
        {
          if(j==0 || j == 7)
          {
            temp->type = rook;
            tempTeams[i][j] = temp;
          }
          else if(j==1 || j == 6)
          {
            temp->type = knight;
            tempTeams[i][j] = temp;
          }
          else if(j==2 || j == 5)
          {
            temp->type = bishop;
            tempTeams[i][j] = temp;
          }
          else if(j == 3)
          {
            temp->type = queen;
            tempTeams[i][j] = temp;
          }
          else if(j == 4)
          {
            temp->type = king;
            tempTeams[i][j] = temp;
          }
        }
      }
    }
  }

  return tempTeams;

}

pieces***
initTeam(teams color)
{
  pieces*** tempTeam = initBlankTeam();
  initpieces(tempTeam,color);

  return tempTeam;

}

pieces***
initBlankTeam()
{
  pieces*** tempTeam = (pieces***)malloc(sizeof(pieces**) * 2);
  for(int i =0; i < rows; i++)
  {
    tempTeam[i] = (pieces**)malloc(sizeof(pieces*) * rows);
  }

  for(int i = 0; i < 2; i++)
  for(int j = 0; j < rows; j++)
  {
    {
      pieces* temp = (pieces*)malloc(sizeof(pieces));
      tempTeam[i][j] = temp;
    }
  }

  return tempTeam;

}

void
freeteam(pieces*** team)
{
  for(int i = 0; i < 2; i++)
  {
    for(int j = 0; j < rows; j++)
    {
      free(team[i][j]);
    }
  }
}

void
printmoves(pieces* piece)
{
  movelist* head = piece->moves;

  if(head == nullptr){
    printf("No Moves Detected for the %d of team %d located at (%d,%d)\n",
            piece->type,piece->team,piece->position->x,piece->position->y);
  }
  else{
    printf("Moves Detected for the %d of team %d located at (%d,%d):\n",
            piece->type,piece->team,piece->position->x,piece->position->y);
    while(head!= nullptr){
      printf("(%d,%d)\n",head->move->x,head->move->y);
      head = head->nextMove;
    }
    printf("\n");
  }
}
