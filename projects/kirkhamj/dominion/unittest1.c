/*****************************************************************
Author:         Joe Kirkham
Created:        2019/05/04
Description:    Tests the implementation of the Smithy function
                refactor from assignment 2.
*****************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testingTools.h"
#include "testingTools.c"
#include <stdio.h>
#include <stdlib.h>

int testSmithyRefactor(struct scen* scen, int v)
{
	int testRet = 0;

	//set up scen minutae
	int handPos = 1; //can be any val but -1
	int curPlayer = 0;
	int otherPlayer = 1; 
	scen->game->handCount[curPlayer] = 5;

	//pre-run vars
	int curPlayerHandPre = scen->game->handCount[curPlayer];
	int curPlayerDeckPre = scen->game->deckCount[curPlayer];
	int otherPlayerHandPre = scen->game->handCount[otherPlayer];
	int otherPlayerDeckPre = scen->game->deckCount[otherPlayer];
	
	//run the test
	int runRet = a2Smithy(&curPlayer, scen->game, &handPos);

	//if return value of the function wasn't 0, then we know something went really wrong.
	if (runRet != 0)
	{
		testRet = -666;
	}
	else
	{
		//post-run vars
		int curPlayerHandPost = scen->game->handCount[curPlayer];
		int curPlayerDeckPost = scen->game->deckCount[curPlayer];
		int otherPlayerHandPost = scen->game->handCount[otherPlayer];
		int otherPlayerDeckPost = scen->game->deckCount[otherPlayer];

		//part 1: did card accurately update cur player values (if any)
		if (v == 1) {printf("expected cur player hand count **%d**, actual **%d**\n\t- ", (curPlayerHandPre + 3 - 1), curPlayerHandPost);}
		if (curPlayerHandPost != (curPlayerHandPre + 3 - 1))
		{
			testRet = -1;
			if (v == 1) {printf("FAIL\n");}
		}
		else if (v == 1) {printf("PASS\n");}

		//part 2: did card use the correct cur player resources (if any)
		if (v == 1) {printf("expected player deck count **%d**, actual **%d**\n\t- ", (curPlayerDeckPre - 3), curPlayerDeckPost);}
		if (curPlayerDeckPost != (curPlayerDeckPre - 3))
		{
			testRet = -1;
			if (v == 1) {printf("FAIL\n");}
		}
		else if (v == 1) {printf("PASS\n");}

		//part 3: did the card (not) have the expected effect on other players if (not) expected
		if (v==1) {printf("expected other player hand count **%d**, actual **%d**\n", otherPlayerHandPre, otherPlayerHandPost);}
		if (otherPlayerHandPre != otherPlayerHandPost)
		{
			testRet = -1;
			if (v == 1) {printf("FAIL\n");}
		}
		else if (v == 1) {printf("PASS\n");}

		//part 4: were other non-player resources (not) affected if effect (not) expected
		if (v==1) {printf("expected other player deck count **%d**, actual **%d**\n", otherPlayerDeckPre, otherPlayerDeckPost);}
		if (otherPlayerDeckPre != otherPlayerDeckPost)
		{
			testRet = -1;
			if (v == 1) {printf("FAIL\n");}
		}
		else if (v == 1) {printf("PASS\n");}
	}

	return testRet;
}

int main(int argc, char *argv[])
{
    //testing vars
    int v = setVerbosity((interpretArgAsInt0to9((int) *argv[1]))); //set test verbosity
    //printf("verbosity = %d", verbosity); //debug
    int testRet;

    //set up test scenario
    struct scen* scen = genScen();

    //smithy
    if (v == 1){printf("**********  TEST INITIALIZED - testSmithyRefactor  **********\n\n");}
    testRet = testSmithyRefactor(scen, v);
	if (v == 1){printf("\n**********  TEST RETURNS - %d  **********\n\n\n", testRet);}


	//dealloc mem
	killScen(scen);

    return 0;
}
