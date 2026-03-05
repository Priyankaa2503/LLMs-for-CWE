/**
 * p3_fc.java - Copy string using computed length with explicit n parameter (Java)
 *
 * Implements a function that copies a source string (e.g., "Hello") into a
 * fixed-size destination buffer. The function takes destination, source,
 * and an explicit number-of-bytes parameter, but it derives the copy size
 * from source.length() instead of trusting the caller-provided n.
 *
 * Validation:
 *  - destination and source must not be null
 *  - n must not be negative
 *  - computed length must not exceed the destination capacity (256)
 *
 * On success it copies exactly source.length() characters and returns true.
 * On failure it returns false without performing a partial copy.
 */

public class p3_fc {

    private static final int DEST_CAPACITY = 256;

    /**
     * Copies {@code src} into {@code dst} using its computed length.
     *
     * @param dst destination buffer (char array) of at least DEST_CAPACITY
     * @param src source string
     * @param n   caller-supplied "number of bytes" (validated for negativity
     *            but not trusted for copy length)
     * @return true on success, false on validation failure
     */
    public static boolean copyStringWithLength(char[] dst, String src, int n) {
        if (dst == null || src == null) {
            System.err.println("Error: destination and source must not be null.");
            return false;
        }

        if (dst.length < DEST_CAPACITY) {
            System.err.println("Error: destination buffer must be at least "
                    + DEST_CAPACITY + " characters.");
            return false;
        }

        if (n < 0) {
            System.err.println("Error: number-of-bytes parameter must not be negative (n=" + n + ").");
            return false;
        }

        int length = src.length();

        if (length > DEST_CAPACITY) {
            System.err.println("Error: source length (" + length
                    + ") exceeds destination capacity (" + DEST_CAPACITY + ").");
            return false;
        }

        src.getChars(0, length, dst, 0);
        if (length < dst.length) {
            dst[length] = '\0';
        }

        return true;
    }

    public static void main(String[] args) {
        char[] dst = new char[DEST_CAPACITY];
        String hello = "Hello";

        // Successful copy.
        if (copyStringWithLength(dst, hello, 5)) {
            System.out.println("Success: \"" + new String(dst, 0, hello.length()) + "\"");
        } else {
            System.out.println("Unexpected failure for valid input.");
        }

        // Failure: overly long string.
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < 300; i++) {
            sb.append('B');
        }
        String longMessage = sb.toString();

        if (!copyStringWithLength(dst, longMessage, 10)) {
            System.out.println("Correctly rejected overly long source string.");
        } else {
            System.out.println("Unexpected success for overly long source string.");
        }
    }
}

