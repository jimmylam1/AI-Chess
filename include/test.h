#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "minimax.h"

//generic test function
void test();

//to test linked list of movelists
void testlinkedlist();

//to ensure that moves are being created accurately
void testGeneratedMoves();

//general test of minimax
void testminimax();

#endif
