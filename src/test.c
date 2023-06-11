#include "../include/test.h"

void test(){
  Game* myGame = initStartBoard();
  printf("----Starting Board-----\n");
  printgame(myGame);
  printf("-----Winner is == %d -----\n",myGame->winner);
  move(myGame,myGame->gameBoard[0][3]->piece,myGame->gameBoard[7][4]);
  printgame(myGame);
  printf("-----Winner is == %d -----\n",myGame->winner);

}

void testminimax(){
  Game* myGame = initStartBoard();
  printf("----Starting Board-----\n");
  printgame(myGame);

  minimax* nextMove;
  for(int i = 0; i < 25 ; i++){
    if(i % 2 == 0){
      nextMove = minORmax(myGame, myGame->whiteTeam);
    }
    else{
      nextMove = minORmax(myGame, myGame->blackTeam);
    }
    printf("-----Board Move %d-----\n",i);
    move(myGame,nextMove->piece,nextMove->move);
    printgame(myGame);
  }
  freeboard(myGame);
}

void testGeneratedMoves(){
  printf("\n\n---------------- Testing Deep Copy of a Board ----------------\n\n");
  Game* myGame = initStartBoard();
  printgame(myGame);

  printf("\n-----The following should contain the entire third row-----\n");
  for(int i = 0; i < rows; i++)
  {
    printmoves(myGame->whiteTeam[1][i]);

  }

  printf("\n-----Moving the Queen to (2,2)-----\n");
  move(myGame,myGame->whiteTeam[0][3], myGame->gameBoard[2][2]);
  printgame(myGame);

  printf("\n-----The Pawn at (1,2) should have no moves-----\n");
  printmoves(myGame->whiteTeam[1][2]);

  printf("\n-----The Queen at (2,2) should have 17 moves-----\n");
  printmoves(myGame->whiteTeam[0][3]);

  printf("\n----- The Queen should endanger pawns at (6,2) and (6,6) -----\n");
  printf("Pawn (6,2) inDanger == %d\n",myGame->gameBoard[6][2]->piece->inDanger);
  printf("Pawn (6,6) inDanger == %d\n",myGame->gameBoard[6][6]->piece->inDanger);


  printf("\n\n---------------- Done Testing Deep Copy ----------------\n\n");
}

void testDeepCopy(){
  printf("\n\n---------------- Testing Deep Copy of a Board ----------------\n\n");
  Game* myGame = initStartBoard();
  Game * newGame = copyboard(myGame);

  move(myGame,myGame->whiteTeam[1][0],myGame->gameBoard[2][0]);

  printf("\n-----The following two boards should be different-----\n");
  printgame(myGame);
  printgame(newGame);

  printf("\n-----The following two Movelists should be different-----\n");
  printf("-----Movelist 1-----\n");
  printmoves(myGame->whiteTeam[1][0]);
  printf("-----Movelist 2-----\n");
  printmoves(newGame->whiteTeam[1][0]);



  freeboard(newGame);
  freeboard(myGame);
  printf("\n\n---------------- Done Testing Deep Copy ----------------\n\n");


}

void testlinkedlist(){
  printf("\n\n---------------- Testing Linked List ---------------- \n\n");
  Game* myGame = initStartBoard();

  printf("-----These should be listed: (2,0)\n");
  printmoves(myGame->whiteTeam[1][0]);



  printf("-----These should be listed: (6,0), (6,2)----- \n");
  move(myGame,myGame->whiteTeam[1][0],myGame->gameBoard[5][1]);
  printmoves(myGame->whiteTeam[1][0]);

  freePieceMoves(myGame->whiteTeam[1][0]);

  printf("-----Nothing should be listed:----- \n");
  printmoves(myGame->whiteTeam[1][0]);

  printf("\n\n---------------- Done Testing Linked List ---------------- \n\n");


}
