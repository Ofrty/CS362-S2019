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

            //update the truthiness of this in-construction Url
            url.valid = (url.valid && tempPair.valid);

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

        //url validator under test
        UrlValidator mut = new UrlValidator();

        //grab ResultPairs from extant test suite and package them for easy acces
        UrlValidatorTest prePairs = new UrlValidatorTest("Random Test Resources");
        ResultPair sourcePairsNoOptions[][] =
        {
            prePairs.testUrlScheme,
            prePairs.testUrlAuthority,
            prePairs.testPath,
            prePairs.testUrlPort,
            prePairs.testUrlQuery
        };

        //create inputs and test each input as it's created.
        //create an array of input URLs. loop through array, inserting a randomly-generated URL at each.
        ResultPair[] inputs;
        inputs = new ResultPair[testCount];

        for (int i = 0; i < testCount; i++)
        {
            inputs[i] = genRandUrl(sourcePairsNoOptions, v);

            //pass to isValid() and assert truthiness
            if (v >= 2){System.out.println("\n*Test\t#" + i + ": url **  " + inputs[i].item + "  ** expected to be **  " + inputs[i].valid + "  **. isValid says: **  " + mut.isValid(inputs[i].item) + "  **");} //verbosity

            //assert truthiness; comment out if you want to run all tests
            //assertEquals(inputs[i].valid, mut.isValid(inputs[i].item));

            //handle fail counts and storage
            if (inputs[i].valid != mut.isValid(inputs[i].item))
            {
                disagreePairs[disagreeCount] = inputs[i];

                disagreeCount++;
            }
        }

        //report final info
        System.out.println("\n\n******************** Finished Random Test Suite on isValid() ********************\n");
        System.out.println("URLs tested:\t" + testCount);
        System.out.println("isValid() agreements:\t" + (testCount - disagreeCount) + " (~ " + ((((float) (testCount - disagreeCount))/(float) testCount) * 100)+ "%)");
        System.out.println("isValid() disagreements:\t" + disagreeCount + " (~ " + (((float) disagreeCount/ (float)testCount) * 100) + "%)");

        //show disagreed pairs if verbosity is 1
        if (v >= 1)
        {
            System.out.println("\n** isValid() disagreed with the expectation for the following result pairs:\n");

            for (int i = 0; i < disagreeCount; i++)
            {
                System.out.println("*#" + i + ": url **  " + disagreePairs[i].item + "  ** was expected to be **  " + disagreePairs[i].valid + "  **, but isValid() said: **  " + (!disagreePairs[i].valid));
            }
        }

        //final assertion: did all of our tests pass?
        assertEquals(0, disagreeCount);
    }
}
