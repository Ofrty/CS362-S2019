import static org.junit.Assert.*;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

public class dumTest {

    @Before
    public void setUp() throws Exception
    {
    }

    @After
    public void tearDown() throws Exception
    {
    }

    @Test
    public void dumTestIncorrect()
    {
        UrlValidator dumUrlVal = new UrlValidator();
        assertTrue(dumUrlVal.isValid("http://www.google.com"));
    }

    @Test
    public void schemaTests()
    {
        UrlValidator smrtUrlVal = new UrlValidator();

        // Positive Tests
        assertTrue(smrtUrlVal.isValid("http://www.google.com"));        // normal URL
        assertTrue(smrtUrlVal.isValid("hTTp://www.google.com"));        // verify different case
        assertTrue(smrtUrlVal.isValid("ftp://www.google.com"));         // Not HTTP or HTTPS

        // Negative Tests
        assertFalse(smrtUrlVal.isValid("httpz://www.google.com"));      // invalid prefix
        assertFalse(smrtUrlVal.isValid("hTTp:/www.google.com"));        // missing forward slash
        assertFalse(smrtUrlVal.isValid(" hTTp://www.google.com"));      // space before url

        // Boundary Tests
        assertFalse(smrtUrlVal.isValid("&#102;&#116;&#112;&#58;&#47;&#47;//www.google.com"));  // Unicode
        assertFalse(smrtUrlVal.isValid("http://"));                     // no entry

    }

    @Test
    public void authorityTests()
    {
        UrlValidator smrtUrlVal = new UrlValidator();


    }


}
