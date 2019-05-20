/*****************************************************************
Author:         Joe Kirkham
Created:        2019/05/04
Description:    See header file for description.
*****************************************************************/

#include "dominion.h"
#include "dominion.c"
#include "rngs.h"
#include "testingTools.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//generates a packaged struct of relevant vars
struct scen* genScen()
{
    struct scen* scen = malloc(sizeof(struct scen));
    scen->game = newGame();

    //set vars
    scen->seed = 1000;
    scen->numPlayer = genRandInt(2, MAX_PLAYERS);
    scen->maxBonus = 10;
    scen->k[0] = adventurer;
    scen->k[1] = council_room;
    scen->k[2] = feast;
    scen->k[3] = gardens;
    scen->k[4] = mine;
    scen->k[5] = remodel;
    scen->k[6] = smithy;
    scen->k[7] = village;
    scen->k[8] = baron;
    scen->k[9] = great_hall;
    scen->maxHandCount = 5;

    //memset(scen->game, 23, sizeof(struct gameState));     // clear the game state
    scen->r = initializeGame(scen->numPlayer, scen->k, scen->seed, scen->game);   // initialize a new game
    //scen->game->handCount[scen->p] = scen->handCount;                  // set the number of cards on hand

    return scen;
};

//dealloc scen
int killScen(struct scen* scen)
{
    memset(scen->game, 0, sizeof(struct gameState));
    scen->game = 0;

    memset(scen, 0, sizeof(struct scen));
    scen = 0;

    return 0;
}

//interprets the provided arg as an int of val 0 to 9
int interpretArgAsInt0to9(int arg)
{
    return (arg - 48);
}

//determine verbosity of tests based on validated user input (if any). set to maximal verbosity if none provided.
int setVerbosity(int v)
{
    int retVal;

    //check input. if value is provided, validate & assign it. otherwise default to max verbosity.
    if (v)
    {
        //validate
        if (v >= VERBOSITY_MIN && v<= VERBOSITY_MAX)
        {
            retVal = v;
        }
        else //not validated, just default to maximal verbosity
        {
            printf("***Provided test verbosity value *%d* invalid - must be between %d-%d (inclusive)\n", v, VERBOSITY_MIN, VERBOSITY_MAX);
            printf("***Defaulting to maximal test verbosity\n\n\n");

            retVal = VERBOSITY_MAX;
        }
    }
    else //not specified, set maximal verbosity
    {
        retVal = VERBOSITY_MAX;
    }

    return retVal;
}

//generate random val between [arg 1, arg2]
int genRandInt(int min, int max)
{
    return (rand() % ((max - min + 1) + min));
}

/* TODO: make standard testing printfs
//print test start announcement to screen
void announceTest(char* s, +)
{
    //set string in mem
    char str[(sizeof(s) + 1)];
    memset(str, '\0', sizeof(str));
    strcpy(str, s);

    printf("*****TEST INITIALIZED - %s", str);
}

//print return value to screen
void announceReturn(int r)
{
	printf("***TEST RETURN VALUE: %d", r);
}
*/
