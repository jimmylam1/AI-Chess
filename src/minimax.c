#include <stdio.h>
#include <stdlib.h>
#include"../include/minimax.h"

// Input: current team.
// Output: difference between current team and other team.
// e.g. current team warscore - other team warscore.
int diffWarScore(Game* myGame, pieces*** current)
{
	int diff;
	if (current[0][0]->team == 1)
	{
		diff =  myGame->WhiteWarScore - myGame->BlackWarScore;
	}
	else
	{
		diff =  myGame->BlackWarScore - myGame->WhiteWarScore;
	}
	return diff;
}




minimax* minORmax(Game* myGame, pieces*** current_team)
{
	minimax* mm = (minimax*)malloc(sizeof(minimax));
	mm->score = -10000;
	if (current_team[0][0]->team > 0)
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < rows; j++)
			{
				if(current_team[i][j]->Alive == 1){
				int currentPieceX = current_team[i][j]->position->x;
				int currentPieceY = current_team[i][j]->position->y;
				board* max_CurrentPiece_move;
				int max_CurrentPiece_score = -10000;
				movelist* current_move = current_team[i][j]->moves;
				if(current_move != NULL){
					while (current_move != NULL)
				{
					Game* tempGame = copyboard(myGame);
					pieces* currentPiece = tempGame->gameBoard[currentPieceX][currentPieceY]->piece;
					int oldWarScore = diffWarScore(tempGame, current_team);
					int currentMoveX = current_move->move->x;
					int currentMoveY = current_move->move->y;
					move(tempGame,currentPiece,tempGame->gameBoard[currentMoveX][currentMoveY]);
					calculateWarScore(tempGame);
					int newWarScore = diffWarScore(tempGame, current_team);


					if (newWarScore > max_CurrentPiece_score)
					{

						max_CurrentPiece_move = current_move->move;
						max_CurrentPiece_score = newWarScore;
					}
					current_move = current_move->nextMove;
					free(tempGame);
				}
			}
				if (max_CurrentPiece_score > mm->score)
				{
					mm->piece = current_team[i][j];
					mm->move = max_CurrentPiece_move;
					mm->score = max_CurrentPiece_score;
				}
			}
		}
		}
	}
	return mm;
}
