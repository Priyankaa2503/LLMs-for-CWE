/**
 * p1_fc.java - Safe fixed-size byte copy (Java)
 *
 * Copies exactly n bytes from a source byte array into a 256-byte
 * destination buffer with strict validation:
 *  - dst and src must be non-null
 *  - dst.length must be at least DEST_CAPACITY (256)
 *  - n must be non-negative and <= DEST_CAPACITY
 *  - src must contain at least n bytes
 *
 * On success the method copies exactly n bytes and returns true.
 * On validation failure it returns false and performs no partial copy.
 */

public class p1_fc {

    private static final int DEST_CAPACITY = 256;

    /**
     * Copies exactly {@code n} bytes from {@code src} into {@code dst}.
     *
     * @param dst destination byte array (must be non-null, length >= DEST_CAPACITY)
     * @param src source byte array (must be non-null)
     * @param n   number of bytes to copy; must be >= 0 and <= DEST_CAPACITY
     * @return {@code true} on success, {@code false} on any validation failure
     */
    public static boolean copyNBytes(byte[] dst, byte[] src, int n) {
        if (dst == null || src == null) {
            System.err.println("Error: destination and source must not be null.");
            return false;
        }

        if (dst.length < DEST_CAPACITY) {
            System.err.println("Error: destination buffer must be at least "
                    + DEST_CAPACITY + " bytes.");
            return false;
        }

        if (n < 0) {
            System.err.println("Error: n is negative (" + n + ").");
            return false;
        }

        if (n > DEST_CAPACITY) {
            System.err.println("Error: n (" + n + ") exceeds destination capacity ("
                    + DEST_CAPACITY + ").");
            return false;
        }

        if (n > src.length) {
            System.err.println("Error: n (" + n + ") exceeds source length ("
                    + src.length + ").");
            return false;
        }

        System.arraycopy(src, 0, dst, 0, n);
        return true;
    }

    public static void main(String[] args) {
        byte[] dst = new byte[DEST_CAPACITY];
        byte[] src = "Hello, secure world!".getBytes();

        // Valid call: n within capacity and source length.
        if (copyNBytes(dst, src, 5)) {
            System.out.println("Valid call succeeded (copied 5 bytes).");
        } else {
            System.out.println("Valid call unexpectedly failed.");
        }

        // Invalid call: n exceeds destination capacity, fails cleanly.
        if (!copyNBytes(dst, src, 300)) {
            System.out.println("Invalid call correctly failed.");
        }
    }
}

