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
        assertFalse(smrtUrlVal.isValid("telnet://www.google.com"));     // non-default scheme
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

        // Note: authority consists of userinfo, hostname, and port
        // userinfo and port are optional
        // scheme://username:password@subdomain.domain.tld:port/path/file-name.suffix?query-string#hash

        // Positive Tests
        assertTrue(smrtUrlVal.isValid("https://www.smrt.com"));         // Just hostname
        assertTrue(smrtUrlVal.isValid("https://ben@smrt.com"));         // Just hostname and username
        assertTrue(smrtUrlVal.isValid("https://ben:neb@smrt.com"));     // Hostname, username, password
        assertTrue(smrtUrlVal.isValid("https://ben@smrt.com:51012"));   // Hotnsame, userinfo, port

        // Negative Tests
        assertFalse(smrtUrlVal.isValid("http://www.smrt..com,"));        // Improper hostname
        assertFalse(smrtUrlVal.isValid("http://ben::neb@smrt.com,"));    // Improper userinfo
        assertFalse(smrtUrlVal.isValid("http://www.smrt.com:5012551,")); // Improper port number

        // Boundary Test

        // Complicated URL
        assertTrue(smrtUrlVal.isValid("http://ben:neb@x.smrt.com/very/long/path.html?p1=v1&p2=v2#more-details"));

        // Unicode
        assertFalse(smrtUrlVal.isValid("hTTp://www.google.&#0099;&#0111;&#0109;"));  // verify different case

    }

    @Test
    public void pathTests()
    {
        UrlValidator smrtUrlVal = new UrlValidator();

        // path of a URL is made of segments that make up a structured hierarchy
        // Each segment is separated by a the / character. Similar to a directory structure.

        // Positive Tests
        assertTrue(smrtUrlVal.isValid("http://www.smrt.com/index.html"));           // normal URL with path
        assertTrue(smrtUrlVal.isValid("http://www.smrt.com/home/1/index.html"));    // longer path
        assertTrue(smrtUrlVal.isValid("ftp://www.smrt.com/~john/doe?w=100&h=50"));  // more complicated path

        // Negative Tests
        assertFalse(smrtUrlVal.isValid("http://www.smrt.com/home//index.html"));  // double forward slash
        assertFalse(smrtUrlVal.isValid("hTTp://www.google.com/home index html")); // spaces in path

        // Boundary Test - Illegal attempt to access parent directory
        assertFalse(smrtUrlVal.isValid("http://www.smrt.com/../file.html"));
    }

    @Test
    public void queryTests()
    {
        UrlValidator smrtUrlVal = new UrlValidator();

        // Query string follows ? character
        // Information usually in key-pair format
        // Each pair is separated by ampersand character

        // Positive Tests
        assertTrue(smrtUrlVal.isValid("http://www.smrt.com?id=1"));                  // single query
        assertTrue(smrtUrlVal.isValid("http://www.smrt.com?id=1&domain=2%test=0"));  // longer query
        assertTrue(smrtUrlVal.isValid("http://www.smrt.com?id=1#some-header"));      // query with fragment

        // Negative Tests
        assertFalse(smrtUrlVal.isValid("http://www.google.com?test = 1"));           // space in query
        assertFalse(smrtUrlVal.isValid("http://www.google.com?test=\n1"));           // other white space char

        // Boundary Tests
        assertTrue(smrtUrlVal.isValid("http://www.smtr.com?test%3D1"));              // URL formatted query
        assertFalse(smrtUrlVal.isValid("http://www.smtr.com%3Ftest%3D1"));            // URL formatted query
    }

    @Test
    public void fragmentTests()
    {
        UrlValidator smrtUrlVal = new UrlValidator();

        // Fragment is a pointer to a secondary resource with the first resource
        // Follows the # character
        // Cannot be null

        // Positive Tests
        assertTrue(smrtUrlVal.isValid("http://www.smrt.com/?index.html#test"));    // normal fragment
        assertTrue(smrtUrlVal.isValid("http://www.smrt.com/?index.html#test1234"));    // alphanumeric fragment
        assertTrue(smrtUrlVal.isValid("http://www.smrt.com/?index.html#test12^&*!"));  // alpha symbol fragment

        assertTrue(smrtUrlVal.isValid("http://www.smrt.com/?index.html#"));           // empty fragment
        assertTrue(smrtUrlVal.isValid("http://www.smrt.com/?index.html#1#2#3"));      // more than one fragment

        // No negative tests possible - fragment part alone cannot make the URL fail

    }

}
