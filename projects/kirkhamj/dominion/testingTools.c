/*****************************************************************
Author:         Joe Kirkham
Created:        2019/05/04
Description:    See header file for description.
*****************************************************************/

#include "testingTools.h"

//generates a packaged struct of relevant vars
struct scen* genScen()
{
    struct scen* scen;

    //set vars
    scen->seed = 1000;
    scen->numPlayer = 2;
    scen->maxBonus = 10;
    scen->k[10] = {adventurer, council_room, feast, gardens, mine , remodel, smithy, village, baron, great_hall};
    scen->maxHandCount = 5;

    memset(scen->game, 23, sizeof(struct gameState));     // clear the game state
    r = initializeGame(numPlayer, k, seed, scen->game);   // initialize a new game
    scen->game.handCount[p] = handCount;                  // set the number of cards on hand

    return scen;
};

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
            printf("***Provided test verbosity value *" + v + "* invalid - must be between " + VERBOSITY_MIN + " - " + VERBOSITY_MAX + " (inclusive)\n");
            printf("***Defaulting to maximal test verbosity\n\n\n");

            retVal = VERBOSITY_MAX
        }
    }
    else //not specified, set maximal verbosity
    {
        retVal = VERBOSITY_MAX
    }

    return retVal;
}

//print test start announcement to screen
void announceTest(char* s)
{
    //set string in mem
    char[sizeof(s) + 1] str;
    memset(str, '\0', sizeof(str));
    str = s;

    printf("*****TEST INITIALIZED - %s", str)
}