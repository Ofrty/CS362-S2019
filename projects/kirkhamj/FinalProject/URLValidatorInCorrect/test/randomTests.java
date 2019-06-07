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

    /*basic test of isValid() for reference*/
    @Test
    public void simpleTest()
    {
        UrlValidator dumUrlVal = new UrlValidator();
        assertTrue(dumUrlVal.isValid("http://www.google.com"));
    }

    @Test
    public void getResultPair()
    {

    }

    @Test
    public void randomTestSuite()
    {
        //set verbosity. 0 = nothing, 1 = min info, 2 = max info
        int v = 2;

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

        //pick from random pairs to assemble a URL
        ResultPair oneUrl = new ResultPair("", true);   //make a new pair object
        for (int i = 0; i < 5; i++) //loop through all Url component types
        {
            //verbosity
            if (v == 2)
            {
                System.out.println("***Url construction at loop iteration " + i + "***");
                System.out.println("item val = *" + oneUrl.item + "* and validity value = *" + oneUrl.valid + "*");
            }

            //pick a randomly-selected item from this Url's component type
            ResultPair tempPair = sourcePairsNoOptions[i][(genRandIntBetweenInclusive(0, (sourcePairsNoOptions[i].length - 1)))];

            //verbosity
            if (v == 2){System.out.println("rand-selected result pair for cur itr is:\n" + tempPair.item + "\n" + tempPair.valid);}

            //append the item of this in-construction Url
            oneUrl.item += tempPair.item;

            //update the truthiness of this in-construction Url
            oneUrl.valid = (oneUrl.valid && tempPair.valid);

            //verbosity
            if (v == 2){System.out.println("Url updated w/ new result pair has item val = *" + oneUrl.item + "* and validity value = *" + oneUrl.valid + "*");}
        }

        //verbosity
        if (v == 2){System.out.println("******\nfinal url pair:\n" + oneUrl.item + "\n" + oneUrl.valid + "\n******");}

        //pass to isValid()

        //assert truthiness

        assertTrue(true);
    }

}
