/*****************************************************************
Author:		 Joe Kirkham
Created:		2019/05/04
Description:	Various common tools to aid in writing tests for dominion code.

Citations (header & implementation):
	Some code & concepts borrowed from the instructor-provided testUpdateCoins.c.
*****************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#include <stdio.h>
#include <stdlib.h>

#ifndef _TESTINGTOOLS_H
#define _TESTINGTOOLS_H

#define VERBOSITY_MIN 0
#define VERBOSITY_MAX 1

//set of vars that can be created on-the-fly for testing specific game scenarios
struct scen
{
	//main vars
	struct gameState* game;
	int i, p, r, handCount;
	int seed;
	int numPlayer;
	int maxBonus;
	int k[10];
	int maxHandCount;
};

/*methods*/
//generate a game scenario (constructor)
struct scen* genScen();

//dealloc scen (destructor)
int killScen(struct scen*);

//interprets the provided arg as an int of val 0 to 9
int interpretArgAsInt0to9(int);

//determine verbosity of tests based on user input (if any). set to maximal verbosity if none provided.
int setVerbosity(int);

//generate random val between [arg 1, arg2] using seed arg3
int genRandInt(int,int);

/* TODO: make standard testing printfs
//formatted prints
void announceTest(char*);
void announceReturn(int);
*/

#endif //_TESTINGTOOLS_H
