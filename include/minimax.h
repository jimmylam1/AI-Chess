#ifndef MINIMAX_H
#define MINIMAX_H
#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "piece.h"
#include "game.h"



typedef struct minimax{
	pieces* piece;
	board* move;
	int score;
} minimax;

minimax* createMM();

minimax* minORmax(Game* myGame, pieces*** current_team);

#endif
