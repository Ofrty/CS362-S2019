package test;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.After;
import org.junit.Test;

import UrlValPackage.*;

public class dum
{
    @Before
    public void setUp() throws Exception {

    }

    @After
    public void tearDown() throws Exception {

    }

    @Test
    public void dumIncorrectTest()
    {
        /*
        String[] dumSchemes = {"http","https"};
        UrlValidator_Incorrect urlVal = new UrlValidator_Incorrect(dumSchemes);
        */

        UrlValidator_Incorrect urlVal = new UrlValidator_Incorrect();

        assertTrue(urlVal.isValid("http:/www.arepublixchickentendersubsonsale.com"));
    }

    @Test
    public void dumCorrectTest()
    {
        String[] dumSchemes = {"http","https"};
        UrlValidator_Correct urlVal = new UrlValidator_Correct(dumSchemes);

        //UrlValidator_Correct urlVal = new UrlValidator_Correct();

        assertTrue(urlVal.isValid("http:/www.arepublixchickentendersubsonsale.com"));
    }
}