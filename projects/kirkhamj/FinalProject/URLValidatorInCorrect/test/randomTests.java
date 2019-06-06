import static org.junit.Assert.*;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

public class randomTests {

    @Before
    public void setUp() throws Exception
    {
    }

    @After
    public void tearDown() throws Exception
    {
    }

    @Test
    public void randomTestA()
    {
        UrlValidator dumUrlVal = new UrlValidator();
        assertTrue(dumUrlVal.isValid("http://www.google.com"));
    }

}
