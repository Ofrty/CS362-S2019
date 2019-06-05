package test;

import junit.framework.TestCase;

import org.junit.Test;

import UrlValPackage.UrlValidator;

public class dum extends TestCase
{
    @Test
    public void dumTest()
    {
        String[] dumSchemes = {"http","https"};
        UrlValidator urlVal = new UrlValidator(dumSchemes);

        assertTrue(urlVal.isValid("http:/www.arepublixchickentendersubsonsale.com"));
    }
}