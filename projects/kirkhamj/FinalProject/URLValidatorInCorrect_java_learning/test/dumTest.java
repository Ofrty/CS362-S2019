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


}
