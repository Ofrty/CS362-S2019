/*****************************************************************
Author:         Joe Kirkham
Created:        2019/05/016
Description:    Randomly tests the implementation of the Adventurer
                function refactored from assignment 2.
*****************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testingTools.h"
#include "testingTools.c"
#include <stdio.h>
#include <stdlib.h>

#define VERBOSITY 1

int randTestAdventurer(struct scen* scen, int v)
{
    int runRet; retVal;

    //randomize game state parameters; compensate for indexes when generating random ints
    int curPlayer = (genRandInt(1, MAX_PLAYERS) - 1);
    int otherPlayer = (genRandInt(1, MAX_PLAYERS) - 1);

    scen->game->deckCount[curPlayer] = (genRandInt(1, MAX_DECK) - 1); //randomize player's deck
    for (int i = 0; i < (scen->game->deckCount[curPlayer]); i++)
    {
        //generate a random card - THIS WILL BE INACCURATE IF THE ENUM IS MODIFIED SUCH THAT THE TREASURE_MAP IS NOT THE LAST ENUM
        scen->game->deck[curPlayer][i] = genRandInt(0, treasure_map);
    }

	scen->game->handCount[curPlayer] = 1; //only care that adventurer is in hand
	scen->game->hand[curPlayer][0] = adventurer;

    //other vars
    int choice1, choice2, choice3;
    choice1 = choice2 = choice3 = -1;
    int coinBonus = 0;

    //calculate pre-run vars
    int preTreasureInHand = 0; //# of treasure in hand pre-run is immaterial here, just care how much it increases by.
	int preHandSize = scen->game->handCount;
	int preDeckSize = scen->game->deckCount[curPlayer];

	int preTreasureInDeck = 0;  //count number of treasure in the player's deck
    for (int i = 0; i < scen->game->deckCount[curPlayer]; i++)
	{
    	if ((scen->game->deck[curPlayer][i] == copper) || (scen->game->deck[curPlayer][i] == silver) || (scen->game->deck[curPlayer][i] == gold))
		{
    		preTreasureInDeck++;
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

    //for reference: args to cardEffect defined in playCard: card, choice1, choice2, choice3, state, handPos, &coin_bonus
    runRet = cardEffect(adventurer, choice1, choice2, choice3, scen, &coinBonus);

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

    //if return value of the function wasn't 0, then we know something went really wrong.
    if (runRet != 0)
    {
        testRet = -666;
    }
    else
    {
        //check values expected to change
        //hand count
		if (v == 1) {printf("expected cur player hand count **%d**, actual **%d**\n\t- ", (preHandSize + expTreasureDiff), posthandSize);}
		if (postHandSize != (preHandSize + expTreasureDiff))
		{
			testRet = -1;
			if (v == 1) {printf("FAIL\n");}
		}
		else if (v == 1) {printf("PASS\n");}

		//treasure in hand
		if (v == 1) {printf("expected cur player treasure in hand count **%d**, actual **%d**\n\t- ", (preTreasureInHand + expTreasureDiff), postTreasureInHand);}
		if (postTreasureInHand != (preTreasureInHand + expTreasureDiff))
		{
			testRet = -1;
			if (v == 1) {printf("FAIL\n");}
		}
		else if (v == 1) {printf("PASS\n");}

		//deck count
		if (v == 1) {printf("expected cur player deck count **%d**, actual **%d**\n\t- ", (preDeckSize - expTreasureDiff), postDeckSize);}
		if (postDeckSize != (preDeckSize - expTreasureDiff))
		{
			testRet = -1;
			if (v == 1) {printf("FAIL\n");}
		}
		else if (v == 1) {printf("PASS\n");}

		//treasure in deck
		if (v == 1) {printf("expected cur player treasure in deck count **%d**, actual **%d**\n\t- ", (preTreasureInDeck - expTreasureDiff), postTreasureInDeck);}
		if (postTreasureInDeck != (preTreasureInDeck - expTreasureDiff))
		{
			testRet = -1;
			if (v == 1) {printf("FAIL\n");}
		}
		else if (v == 1) {printf("PASS\n");}
    }

	return testRet;

/**a3 unit test
    //set up scen minutae
    int curDrawnTreasure = 0;
    int curCardDrawn;
    int curTempHand[MAX_HAND];
    int curZ = 0;
    int curPlayer = 0;
    int otherPlayer = 1;
    scen->game->deckCount[curPlayer] = 4; //deliberately setting deck to size 4 with treasure = 2
    scen->game->deck[curPlayer][0] = copper;
    scen->game->deck[curPlayer][1] = estate;
    scen->game->deck[curPlayer][2] = smithy;
    scen->game->deck[curPlayer][3] = gold;

    //pre-run vars
    int curPlayerHandCountPre = scen->game->handCount[curPlayer];
    int curPlayerDeckCountPre = scen->game->deckCount[curPlayer];
    int otherPlayerHandPre = scen->game->handCount[otherPlayer];
    int otherPlayerDeckPre = scen->game->deckCount[otherPlayer];
    int supplyPre[sizeof(scen->game->supplyCount)];
    memcpy(supplyPre, scen->game->supplyCount, sizeof(supplyPre));

    /////////////////////////////////
    //int curPlayerHandPre[MAX_HAND];
    //memcpy(curPlayerHandPre, scen->game->hand[curPlayer], MAX_HAND);
    //int curPlayerDeckPre[MAX_DECK];
    //memcpy(curPlayerDeckPre, scen->game->deck[curPlayer], MAX_DECK);
    ////////////////////////////////

    //run the test
    int runRet = a2Adventurer(&curDrawnTreasure, scen->game, &curPlayer, &curCardDrawn, curTempHand, &curZ);

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
        int otherPlayerHandPost = scen->game->handCount[otherPlayer];
        int otherPlayerDeckPost = scen->game->deckCount[otherPlayer];
        int supplyPost[sizeof(scen->game->supplyCount)];
        memcpy(supplyPost, scen->game->supplyCount, sizeof(supplyPost));

        ////////////////////////////////
        int curPlayerHandPost[MAX_HAND];
        memcpy(curPlayerHandPost, scen->game->hand[curPlayer], MAX_HAND);
        int curPlayerDeckPost[MAX_DECK];
        memcpy(curPlayerDeckPost, scen->game->deck[curPlayer], MAX_DECK);
        ////////////////////////////////

        //part 1: did card accurately update cur player values (if any)
        //check hand count
        if (v == 1) {printf("expected cur player hand count **%d**, actual **%d**\n\t- ", (curPlayerHandCountPre + 2 - 1), curPlayerHandCountPost);}
        if (curPlayerHandCountPost != (curPlayerHandCountPre + 2 - 1))
        {
            testRet = -1;
            if (v == 1) {printf("FAIL\n");}
        }
        else if (v == 1) {printf("PASS\n");}

        //part 2: did card use the correct cur player resources (if any)
        //check deck count - expect all cards to be flipped
        if (v == 1) {printf("expected player deck count **%d**, actual **%d**\n\t- ", (curPlayerDeckCountPre - 4), curPlayerDeckCountPost);}
        if (curPlayerDeckCountPost != (curPlayerDeckCountPre - 2))
        {
            testRet = -1;
            if (v == 1) {printf("FAIL\n");}
        }
        else if (v == 1) {printf("PASS\n");}

        /part 3: did the card (not) have the expected effect on other players if (not) expected
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

        /part 4: were other non-player resources (not) affected if effect (not) expected
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
**/
}

int main() //(int argc, char *argv[])
{
    //testing vars
    //int v = setVerbosity((interpretArgAsInt0to9((int) *argv[1]))); //set test verbosity
    int testRet;

    //set up test scenario
    struct scen* scen = genScen();

    //run
    if (VERBOSITY == 1){printf("**********  TEST INITIALIZED - testSmithyRefactor  **********\n\n");}
    testRet = randTestAdventurer(scen, VERBOSITY);
    if (VERBOSITY == 1){printf("\n**********  TEST RETURNS - %d  **********\n\n\n", testRet);}

    //dealloc mem
    killScen(scen);

    return 0;
}