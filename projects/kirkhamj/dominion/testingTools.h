/*****************************************************************
Author:         Joe Kirkham
Created:        2019/05/04
Description:    Various common tools to aid in writing tests for dominion code.

Citations:
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
    int seed = 1000;
    int numPlayer = 2;
    int maxBonus = 10;
    int k[10] = {adventurer, council_room, feast, gardens, mine
            , remodel, smithy, village, baron, great_hall};
    int maxHandCount = 5;

    // arrays of all coppers, silvers, and golds
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];

    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }
};

/*methods*/
//generate a game scenario
struct scen* genScen();

//determine verbosity of tests based on user input (if any). set to maximal verbosity if none provided.
int setVerbosity(int);

//print test start announcement to screen
void announceTest(char*);

#endif //_TESTINGTOOLS_H
