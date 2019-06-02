/*****************************************************************
Author:			Joe Kirkham
Created:		2019/05/16
Description:	Randomly tests the implementation of the Adventurer
				function refactored from assignment 2.
*****************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testingTools.h"
#include "testingTools.c"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define TEST_COUNT 10000
#define VERBOSITY 0

int randTestAdventurer(struct scen* scen, int v)
{
	int runRet, retVal;

	//randomize game state parameters; compensate for indexes when generating random ints
	int curPlayer = 0;
	scen->game->deckCount[curPlayer] = genRandInt(0, 20); //randomize player's deck

	for (int i = 0; i < (scen->game->deckCount[curPlayer]); i++)
	{

		//generate a random card - THIS WILL BE INACCURATE IF THE ENUM IS MODIFIED SUCH THAT THE TREASURE_MAP IS NOT THE LAST ENUM
		scen->game->deck[curPlayer][i] = genRandInt(0, treasure_map);

		//high berbosity
		if(v==2){printf("cur player deck idx %d is a %d\n", i, scen->game->deck[curPlayer][i]);}
	}

	//high verbosity
	if(v==2){printf("randtestadventurer: deck count for curplayer is %d\n",scen->game->deckCount[curPlayer]);}

	scen->game->hand[curPlayer][0] = adventurer; //only care that adventurer is in hand

	//other vars
	scen->game->whoseTurn = curPlayer;
	int handPos = 0;
	int choice1, choice2, choice3;
	choice1 = choice2 = choice3 = -1;
	int coinBonus = 0;

	//calculate pre-run vars
	int preHandSize = scen->game->handCount[curPlayer];
	int preDeckSize = scen->game->deckCount[curPlayer];

	int preTreasureInDeck = 0;  //count number of treasure in the player's deck
	for (int i = 0; i < scen->game->deckCount[curPlayer]; i++)
	{
		if ((scen->game->deck[curPlayer][i] == copper) || (scen->game->deck[curPlayer][i] == silver) || (scen->game->deck[curPlayer][i] == gold))
		{
			preTreasureInDeck++;
		}
	}

	int preTreasureInHand = 0; //count number of treasure in the player's hand
	for (int i = 0; i < scen->game->handCount[curPlayer]; i++)
	{
		if ((scen->game->hand[curPlayer][i] == copper) || (scen->game->hand[curPlayer][i] == silver) || (scen->game->hand[curPlayer][i] == gold))
		{
			preTreasureInHand++;
		}

	}

	int expTreasureDiff; //how do we expect the treasure value to change?
	if (preTreasureInDeck >= 2) //if 2 or more in deck then 2. else however many are in deck (0 or 1).
	{
		expTreasureDiff = 2;
	}
	else
	{
		expTreasureDiff = preTreasureInDeck;
	}

	//low verbosity
	if(v==1){printf("pre-run: expected treature diff is %d\n", expTreasureDiff);}

	//high verbosity
	if (v == 2){printf("pretreasinhand = %d; prehandsize = %d, predecksize = %d\n", preTreasureInHand, preHandSize, preDeckSize);}

	//run test
	//for reference: args to cardEffect defined in playCard: card, choice1, choice2, choice3, state, handPos, &coin_bonus
	runRet = cardEffect(adventurer, choice1, choice2, choice3, scen->game, handPos, &coinBonus);

	//calculate post-run vars
	int postHandSize = scen->game->handCount[curPlayer];
	int postDeckSize = scen->game->deckCount[curPlayer];

	int postTreasureInDeck = 0; //count treasure in deck
	for (int i = 0; i < scen->game->deckCount[curPlayer]; i++)
	{
		if ((scen->game->deck[curPlayer][i] == copper) || (scen->game->deck[curPlayer][i] == silver) || (scen->game->deck[curPlayer][i] == gold))
		{
			postTreasureInDeck++;
		}
	}

	int postTreasureInHand = 0;  //count treasure in hand
	for (int i = 0; i < scen->game->handCount[curPlayer]; i++)
	{
		if ((scen->game->hand[curPlayer][i] == copper) || (scen->game->hand[curPlayer][i] == silver) || (scen->game->hand[curPlayer][i] == gold))
		{
			postTreasureInHand++;
		}

	}

	//high verbosity
	if(v==2){printf("postreasinhand = %d; posthandsize = %d, postdecksize = %d\n", postTreasureInHand, postHandSize, postDeckSize);} //debug

/*
	//if return value of the function wasn't 0, then we know something went really wrong.
	if (runRet != 0)
	{
		runRet = -666;
	}
	else
	{
*/
	//check values expected to change
	//hand count
	if (v >= 1) {printf("expected cur player hand count **%d**, actual **%d**\n\t- ", (preHandSize + expTreasureDiff - 1), postHandSize);} //-1 to account for the loss of the adventurer card
	if (postHandSize != (preHandSize + expTreasureDiff - 1))
	{
		retVal = -1;
		if (v >= 1) {printf("FAIL\n");}
	}
	else if (v >= 1) {printf("PASS\n");}

	//treasure in hand
	if (v >= 1) {printf("expected cur player treasure in hand count **%d**, actual **%d**\n\t- ", (preTreasureInHand + expTreasureDiff), postTreasureInHand);}
	if (postTreasureInHand != (preTreasureInHand + expTreasureDiff))
	{
		retVal = -1;
		if (v >= 1) {printf("FAIL\n");}
	}
	else if (v >= 1) {printf("PASS\n");}

	//deck count
	if (v >= 1) {printf("expected cur player deck count <= **%d**, actual **%d**\n\t- ", (preDeckSize - expTreasureDiff), postDeckSize);}
	if (postDeckSize > (preDeckSize - expTreasureDiff))
	{
		retVal = -1;
		if (v >= 1) {printf("FAIL\n");}
	}
	else if (v >= 1) {printf("PASS\n");}

	//treasure in deck
	if (v >= 1) {printf("expected cur player treasure in deck count **%d**, actual **%d**\n\t- ", (preTreasureInDeck - expTreasureDiff), postTreasureInDeck);}
	if (postTreasureInDeck != (preTreasureInDeck - expTreasureDiff))
	{
		retVal = -1;
		if (v >= 1) {printf("FAIL\n");}
	}
	else if (v >= 1) {printf("PASS\n");}
	// }
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
	{printf("**********  TEST INITIALIZED - testAdventurerRefactor  **********\n\n");}
	for (int i = 0; i < TEST_COUNT; i++)
	{
		//set up test scenario
		struct scen* scen = genScen();

		testRet = randTestAdventurer(scen, VERBOSITY);

		if (VERBOSITY >= 1){printf("\n**********  TEST RETURNS - %d  **********\n\n\n", testRet);}

		if (testRet == -1){failCount++;}//tally fail count

		//dealloc mem
		killScen(scen);
	}

	//announce test fail/run ratio
	printf("*****FINAL RESULTS*****\n\nRuns:  %d\nFails: %d\n\nFailure Rate: ~%.3f%%\n\n***************\n\n",TEST_COUNT,failCount,((float) failCount / (float) TEST_COUNT)*100);

	return 0;
}
