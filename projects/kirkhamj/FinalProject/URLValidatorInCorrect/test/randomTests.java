import static org.junit.Assert.*;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import java.util.Random;
import java.util.Arrays;

public class randomTests {

    @Before
    public void setUp() throws Exception
    {
    }

    @After
    public void tearDown() throws Exception
    {
    }

    /*
    genRandBetweenInclusive() is a support function that generates a random integer.

    Citation: https://www.geeksforgeeks.org/generating-random-numbers-in-java/
    */
    public int genRandIntBetweenInclusive(int min, int max)
    {
        Random r = new Random();

        //the nextInt just returns a value b/t 0 and its argument. compensate for min.
        int v = (r.nextInt(((max + 1) - min)) + min);

        return v;
    }

    /*simple unit test for the random generator*/
    @Test
    public void testIntRandomizer()
    {
        //generate some test min/max values
        int minA = 0;
        int maxA = 20;
        int minB = -5;
        int maxB = 5;
        int minC = 0;
        int maxC = 0;

        //put them through the random generator
        int vA = genRandIntBetweenInclusive(minA, maxA);
        int vB = genRandIntBetweenInclusive(minB, maxB);
        int vC = genRandIntBetweenInclusive(minC, maxC);

        //print for verbosity
        System.out.println("genRandIntBetweenInclusive: generated a value of **" + vA + "* using range [" + minA + "," + maxA + "]");
        System.out.println("genRandIntBetweenInclusive: generated a value of **" + vB + "* using range [" + minB + "," + maxB + "]");
        System.out.println("genRandIntBetweenInclusive: generated a value of **" + vC + "* using range [" + minC + "," + maxC + "]");

        //check with nested asserts
        assertTrue(((vA >= minA) && (vA <= maxA)));
        assertTrue(((vB >= minB) && (vB <= maxB)));
        assertTrue(((vC >= minC) && (vC <= maxC)));
    }

    /*given a 2D-array of Url components in arg1, assemble and return a randomly-generated candidate Url ResultPair. arg2 is verbosity level.*/
    //public ResultPair genRandUrl(ResultPair[][] sourcePairs, long schemeOption, int v) // abandoned attempt to randomize all schemes
    public ResultPair genRandUrl(ResultPair[][] sourcePairs, int v)
    {
        //pick from random URL components to assemble a URL
        ResultPair url = new ResultPair("", true);   //make a new pair object
        for (int i = 0; i < 5; i++) //loop through all Url component types
        {
            //verbosity
            if (v >= 3)
            {
                System.out.println("***Url construction at loop iteration " + i + "***");
                System.out.println("item val = *" + url.item + "* and validity value = *" + url.valid + "*");
            }

            //pick a randomly-selected item from this Url's component type
            ResultPair tempPair = sourcePairs[i][(genRandIntBetweenInclusive(0, (sourcePairs[i].length - 1)))];

            //verbosity
            if (v >= 3){System.out.println("rand-selected result pair for cur itr is:\n" + tempPair.item + "\n" + tempPair.valid);}

            //append the item of this in-construction Url
            url.item += tempPair.item;

            //update the truthiness of this in-construction Url.
            url.valid = (url.valid && tempPair.valid);

            /* abandoned attempt to randomize ALLOW_ALL_SCHEMES
            //update the truthiness of this in-construction Url.
            // account for schemes options: if either we're past the scheme component OR ALLOW_ALL_SCHEMES is off...
            // ... then go ahead and update the under-construction Url's validity based on the value of the new component ...
            // ... otherwise, we must be at the scheme component and ALLOW_ALL must be on. nothing will change because the scheme will always be true.
            if ( (i != 0) || (schemeOption == 0) )
            {
                url.valid = (url.valid && tempPair.valid);
            }
            */

            //verbosity
            if (v >= 3){System.out.println("Url updated w/ new result pair has item val = *" + url.item + "* and validity value = *" + url.valid + "*");}
        }

        return url;
    }

    /*basic test of isValid() for reference*/
    @Test
    public void simpleTest()
    {
        UrlValidator dumUrlVal = new UrlValidator();
        assertTrue(dumUrlVal.isValid("http://www.google.com"));
    }

    @Test
    public void randomTestSuite()
    {
        //set general test parameters and counters
        int testCount = 1000;
        int disagreeCount = 0;

        //set verbosity. 0 = essential info, 1 = show failed pairs, 2 = show all tests, 3 = debug info for our test functions
        int v = 1;

        //storage for failed pairs; pre-fill with nulls
        ResultPair[] disagreePairs;
        disagreePairs = new ResultPair[testCount];
        Arrays.fill(disagreePairs, null);

        System.out.println("\n\n******************** Starting Random Test Suite on isValid() ********************\n\n");

        //create new Url validator with option to allow all schemes
        long allow = UrlValidator.ALLOW_ALL_SCHEMES;
        UrlValidator mut = new UrlValidator(allow);

        /* abandoned attempt to randomize all schemes
        //randomize ALLOW_ALL_SCHEMES option for every test and store in a separate array
        long allowAllSchemesBools[];
        allowAllSchemesBools = new long[testCount];

        for (int i = 0; i < testCount; i++)
        {
            allowAllSchemesBools[i] = (UrlValidator.ALLOW_ALL_SCHEMES * genRandIntBetweenInclusive(0,1));
        }
        */

        /* abandoned attempt B to randomize ALLOW_ALL_SCHEMES
        //randomize ALLOW_ALL_SCHEMES and create the MUT dependent on this
        int allowAllSchemesBool = genRandIntBetweenInclusive(0,1);
        UrlValidator mut;
        if ((allowAllSchemesBool == 1))
        {
            //yes - allow all schemes
            long allow = UrlValidator.ALLOW_ALL_SCHEMES;
            mut = new UrlValidator(allow);
        }
        else
        {
            //no - do not allow all schemes (default)
            mut = new UrlValidator();
        }
        */

        //grab ResultPairs from extant test suite and package them for easy acces
        UrlValidatorTest prePairs = new UrlValidatorTest("Random Test Resources");
        ResultPair sourcePairsNoOptions[][] =
        {
            prePairs.testUrlScheme,
            prePairs.testUrlAuthority,
            prePairs.testUrlPort,
            prePairs.testPath,
            prePairs.testUrlQuery
        };

        //create inputs and test each input as it's created.
        //create an array of input URLs. loop through array, inserting a randomly-generated URL at each.
        ResultPair[] inputs;
        inputs = new ResultPair[testCount];

        for (int i = 0; i < testCount; i++)
        {
            //make a URL based on the available options and the ALL_SCHEMES options
            //inputs[i] = genRandUrl(sourcePairsNoOptions, allowAllSchemesBool, v); //abandoned attempt to randomize ALLOW_ALL_SCHEMES
            inputs[i] = genRandUrl(sourcePairsNoOptions, v);

            //pass to isValid() and assert truthiness
            if (v >= 2){System.out.println("\n*Test\t#" + i + ": url **  " + inputs[i].item + "  ** expected to be **  " + inputs[i].valid + "  **. isValid says: **  " + mut.isValid(inputs[i].item) + "  **");} //verbosity

            //assert truthiness. leave "on" to abort test at the first failure. comment out if you want to run all tests.
            //assertEquals(inputs[i].valid, mut.isValid(inputs[i].item));

            //handle fail counts and storage
            if (inputs[i].valid != mut.isValid(inputs[i].item))
            {
                mut.isValid(inputs[i].item); //debug; just doing it again for a breakpoint

                disagreePairs[disagreeCount] = inputs[i];

                disagreeCount++;
            }
        }

        //report final info
        System.out.println("\n\n******************** Finished Random Test Suite on isValid() ********************\n");
        System.out.println("URLs tested:\t" + testCount);
        System.out.println("isValid() agreements:\t" + (testCount - disagreeCount) + " (" + ((((float) (testCount - disagreeCount))/(float) testCount) * 100)+ "%)");
        System.out.println("isValid() disagreements:\t" + disagreeCount + " (" + (((float) disagreeCount/ (float)testCount) * 100) + "%)");

        //show disagreed pairs if verbosity is 1
        if (v >= 1)
        {
            if (disagreeCount > 0)
            {
                System.out.println("\n** isValid() disagreed with the expectation for the following URLs:\n");

                for (int i = 0; i < disagreeCount; i++)
                {
                    System.out.println("*#" + i + ": url **  " + disagreePairs[i].item + "  ** was expected to be **  " + disagreePairs[i].valid + "  **, but isValid() said: **  " + (!disagreePairs[i].valid) + "  **");
                }
            }
            else
            {
                System.out.println("\n** isValid() agreed with the expectations for all URLs.\n");
            }
        }

        //final assertion: did all of our tests pass? this may not execute if each input is asserted individually and one of them fails
        assertEquals(0, disagreeCount);
    }
}
