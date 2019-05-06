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
	int testRet;

	//pre-run vars
	int curPlayerHandPreRun = scen->game->handCount;

	printf("\npoint a\n");

	//run the test
	int runRet = a2Smithy(whoseTurn(scen->game), scen->game, 1);

	printf("\npoint b\n");

	//if return value of the function wasn't 0, then we know something went really wrong.
	if (!runRet)
	{
		testRet = -666;
	}
	else
	{
		//post-run vars
		int curPlayerHandPostRun = scen->game->handCount;

		//part 1: did card accurately update cur player values (if any)
		if (curPlayerHandPostRun != (curPlayerHandPreRun + 3))
		{
			testRet = -1;
		}

		//part 2: did card use the correct cur player resources (if any)



		//part 3: did the card (not) have the expected effect on other players if (not) expected



		//part 4: were other non-player resources (not) affected if effect (not) expected

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
	if (v == 1){printf("**********  TEST RETURNS - %d  **********\n\n\n", testRet);}


	//dealloc mem
	killScen(scen);

    return 0;
}
