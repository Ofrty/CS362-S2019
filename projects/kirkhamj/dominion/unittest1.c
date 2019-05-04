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
#include <stdio.h>
#include <stdlib.h>

int testSmithRefactor(v)
{
    //part 1: did card accurately update cur player values (if any)



    //part 2: did card use the correct cur player resources (if any)



    //part 3: did the card (not) have the expected effect on other players if (not) expected



    //part 4: were other non-player resources (not) affected if effect (not) expected


    return 0;
}

int main(int argc, char *argv[])
{
    //set test verbosity
    int verbosity = setVerbosity((int) *argv[1]);

    //set up test scenario
    struct scen* = genScen();

    //smithy
    if (verbosity === 1) {announceTest("refactored Smithy")}
    testSmithyRefactor(verbosity);
    if (verbosity === 1) {announceTest("refactored Smithy", )}

    return 0;
}
