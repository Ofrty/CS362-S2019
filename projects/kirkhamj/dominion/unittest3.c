/*****************************************************************
Author:         Joe Kirkham
Created:        2019/05/04
Description:    Tests the implementation of the Village function
                refactor from assignment 2.
*****************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testingTools.h"
#include "testingTools.c"
#include <stdio.h>
#include <stdlib.h>

#define VERBOSITY 1

int testVillageRefactor(struct scen* scen, int v)
{
	int testRet = 0;

	//set up scen minutae
	int handPos = 0;
	int curPlayer = 0;
	int otherPlayer = 1;

	//pre-run vars
	int curPlayerHandCountPre = scen->game->handCount[curPlayer];
	int curPlayerDeckCountPre = scen->game->deckCount[curPlayer];
	int curPlayerActionsPre = scen->game->numActions;
	int otherPlayerHandPre = scen->game->handCount[otherPlayer];
	int otherPlayerDeckPre = scen->game->deckCount[otherPlayer];
	int supplyPre[sizeof(scen->game->supplyCount)];
	memcpy(supplyPre, scen->game->supplyCount, sizeof(supplyPre));
	
	//run the test
	int runRet = a2Village(&curPlayer, scen->game, &handPos);

	//if return value of the function wasn't 0, then we know something went really wrong.
	if (runRet != 0)
	{
		testRet = -666;
	}
	else
	{
		//post-run vars
		int curPlayerHandCountPost = scen->game->handCount[curPlayer];
		int curPlayerDeckCountPost = scen->game->deckCount[curPlayer];
		int curPlayerActionsPost = scen->game->numActions;
		int otherPlayerHandPost = scen->game->handCount[otherPlayer];
		int otherPlayerDeckPost = scen->game->deckCount[otherPlayer];
		int supplyPost[sizeof(scen->game->supplyCount)];
		memcpy(supplyPost, scen->game->supplyCount, sizeof(supplyPost));


		/*part 1: did card accurately update cur player values (if any)*/
		//check hand count
		if (v == 1) {printf("expected cur player hand count **%d**, actual **%d**\n\t- ", (curPlayerHandCountPre + 1 - 1), curPlayerHandCountPost);}
		if (curPlayerHandCountPost != (curPlayerHandCountPre + 1 - 1))
		{
			testRet = -1;
			if (v == 1) {printf("FAIL\n");}
		}
		else if (v == 1) {printf("PASS\n");}

		//check actions
		if (v == 1) {printf("expected cur player action count **%d**, actual **%d**\n\t- ", (curPlayerActionsPre + 2), curPlayerActionsPost);}
		if (curPlayerHandCountPost != (curPlayerHandCountPre + 2))
		{
			testRet = -1;
			if (v == 1) {printf("FAIL\n");}
		}
		else if (v == 1) {printf("PASS\n");}

		//*part 2: did card use the correct cur player resources (if any)*/
		//check deck count
		if (v == 1) {printf("expected player deck count **%d**, actual **%d**\n\t- ", (curPlayerDeckCountPre - 1), curPlayerDeckCountPost);}
		if (curPlayerDeckCountPost != (curPlayerDeckCountPre - 1))
		{
			testRet = -1;
			if (v == 1) {printf("FAIL\n");}
		}
		else if (v == 1) {printf("PASS\n");}

		/*part 3: did the card (not) have the expected effect on other players if (not) expected*/
		//check other player's hand count
		if (v==1) {printf("expected other player hand count **%d**, actual **%d**\n\t- ", otherPlayerHandPre, otherPlayerHandPost);}
		if (otherPlayerHandPre != otherPlayerHandPost)
		{
			testRet = -1;
			if (v == 1) {printf("FAIL\n");}
		}
		else if (v == 1) {printf("PASS\n");}

		//check other player's deck count
		if (v==1) {printf("expected other player deck count **%d**, actual **%d**\n\t- ", otherPlayerDeckPre, otherPlayerDeckPost);}
		if (otherPlayerDeckPre != otherPlayerDeckPost)
		{
			testRet = -1;
			if (v == 1) {printf("FAIL\n");}
		}
		else if (v == 1) {printf("PASS\n");}

		/*part 4: were other non-player resources (not) affected if effect (not) expected*/
		//check the kingdom
		for (int s = 0; s < treasure_map+1; s++)
		{
			if (v==1) {printf("expected supply pile %d count **%d**, actual **%d**\n\t- ", s, supplyPre[s], supplyPost[s]);}
			if (supplyPre[s] != supplyPost[s])
			{
				testRet = -1;
				if (v == 1) {printf("FAIL\n");}
			}
			else if (v == 1) {printf("PASS\n");}
		}
	}

	return testRet;
}

int main() //(int argc, char *argv[])
{
    //testing vars
    //int v = setVerbosity((interpretArgAsInt0to9((int) *argv[1]))); //set test verbosity
    int testRet;

    //set up test scenario
    struct scen* scen = genScen();

    //run
    if (VERBOSITY == 1){printf("**********  TEST INITIALIZED - testVillageRefactor  **********\n\n");}
    testRet = testVillageRefactor(scen, VERBOSITY);
	if (VERBOSITY == 1){printf("\n**********  TEST RETURNS - %d  **********\n\n\n", testRet);}


	//dealloc mem
	killScen(scen);

    return 0;
}
