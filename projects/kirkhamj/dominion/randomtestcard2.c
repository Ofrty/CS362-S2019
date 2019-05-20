/*****************************************************************
Author:			Joe Kirkham
Created:		2019/05/19
Description:	Randomly tests the implementation of the Village
				function refactored from assignment 2.
*****************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testingTools.h"
#include "testingTools.c"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TEST_COUNT 1
#define VERBOSITY 1

int randTestVillage(struct scen* scen, int v)
{
	int runRet, retVal;

	//randomize game state parameters; compensate for indexes when generating random ints
	scen->game->deckCount[curPlayer] = genRandInt(0, 10); //randomize player's deck

	for (int i = 0; i < (scen->game->deckCount[curPlayer]); i++)
	{
		//generate a random card - THIS WILL BE INACCURATE IF THE ENUM IS MODIFIED SUCH THAT THE TREASURE_MAP IS NOT THE LAST ENUM
		scen->game->deck[curPlayer][i] = genRandInt(0, treasure_map);

		//high berbosity
		if(v==2){printf("cur player deck idx %d is a %d\n", i, scen->game->deck[curPlayer][i]);}
	}

	//high verbosity
	if(v==2){printf("randtestvillage: deck count for curplayer is %d\n",scen->game->deckCount[curPlayer]);}

	scen->game->hand[curPlayer][0] = village; //only care that village is in the hand

	//other vars
	int curPlayer = 0;
	scen->game->whoseTurn = curPlayer;
	int handPos = 0;
	int choice1, choice2, choice3;
	choice1 = choice2 = choice3 = -1;
	int coinBonus = 0;

	//calculate pre-run vars
	int preHandSize = scen->game->handCount[curPlayer];
	int preDeckSize = scen->game->deckCount[curPlayer];
	int preActions = scen->game->numActions;

	for (int i = 0; i < scen->game->handCount[curPlayer]; i++)
	{
		if ((scen->game->hand[curPlayer][i] == copper) || (scen->game->hand[curPlayer][i] == silver) || (scen->game->hand[curPlayer][i] == gold))
		{
			preTreasureInHand++;
		}

	}

	int expDiff; //how do we expect the deck/hand value to change?
	if (scen->game->deckCount[curPlayer] >= 3) //if 3 or more in deck then 3. else however many are in deck (0 or 1 or 2).
	{
		expDiff = 3;
	}
	else
	{
		expDiff = scen->game->deckCount[curPlayer];
	}

	//low verbosity
	if(v==1){printf("pre-run: expected deck/hand diff is %d\n", expDiff);}

	//high verbosity
	if (v == 2){printf("prehandsize = %d, predecksize = %d, preActions = %d\n", preHandSize, preDeckSize, preActions);}

	//run test
	//for reference: args to cardEffect defined in playCard: card, choice1, choice2, choice3, state, handPos, &coin_bonus
	runRet = cardEffect(village, choice1, choice2, choice3, scen->game, handPos, &coinBonus);

	//calculate post-run vars
	int postHandSize = scen->game->handCount[curPlayer];
	int postDeckSize = scen->game->deckCount[curPlayer];
	int postActions = scen->game->numActions;

	//high verbosity
	if(v==2){printf("posthandsize = %d, postdecksize = %d, postActions = %d\n", postHandSize, postDeckSize, postActions);} //debug

	//if return value of the function wasn't 0, then we know something went really wrong.
	if (runRet != 0)
	{
		runRet = -666;
	}
	else
	{
		//check values expected to change
		//hand count
		if (v == 1) {printf("expected cur player hand count **%d**, actual **%d**\n\t- ", (preHandSize + expDiff), postHandSize);}
		if (postHandSize != (preHandSize + expDiff))
		{
			retVal = -1;
			if (v == 1) {printf("FAIL\n");}
		}
		else if (v == 1) {printf("PASS\n");}

		//deck count
		if (v == 1) {printf("expected cur player deck count <= **%d**, actual **%d**\n\t- ", (preDeckSize - expDiff), postDeckSize);}
		if (postDeckSize > (preDeckSize - expDiff))
		{
			retVal = -1;
			if (v == 1) {printf("FAIL\n");}
		}
		else if (v == 1) {printf("PASS\n");}

		//action count
		if (v == 1) {printf("expected action count = **%d**, actual **%d**\n\t- ", (preActions + 2 - 1), postActions);} //-1 for the action of using the village card itself
		if (postActions != (preActions + 2 - 1))
		{
			retVal = -1;
			if (v == 1) {printf("FAIL\n");}
		}
		else if (v == 1) {printf("PASS\n");}
	}
	return retVal;
}

int main() //(int argc, char *argv[])
{
	//testing vars
	//int v = setVerbosity((interpretArgAsInt0to9((int) *argv[1]))); //set test verbosity
	int testRet;
	int failCount = 0;

	srand(time(NULL));

	//run
	printf("**********  TEST INITIALIZED - testVillageRefactor  **********\n\n");
	for (int i = 0; i < TEST_COUNT; i++)
	{
		//set up test scenario
		struct scen* scen = genScen();

		testRet = randTestAdventurer(scen, VERBOSITY);

		if (VERBOSITY == 1){printf("\n**********  TEST RETURNS - %d  **********\n\n\n", testRet);}

		if (testRet == -1){failCount++;} //tally fail count

		//dealloc mem
		killScen(scen);
	}

	//announce test fail/run ratio
	printf("*****FINAL RESULTS*****\n\nRuns:  %d\nFails: %d\n\nFailure Rate: ~%.3f%%\n\n***************\n\n",TEST_COUNT,failCount,((float) failCount / (float) TEST_COUNT)*100);

	return 0;
}
