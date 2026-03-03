public class p1_nc {

    private static final int DEST_CAPACITY = 256;

    /**
     * Copies exactly {@code n} bytes from {@code src} into {@code dst}.
     *
     * @param dst destination byte array (must be non-null, length >= 256)
     * @param src source byte array (must be non-null)
     * @param n   number of bytes to copy; must be >= 0 and <= DEST_CAPACITY
     * @return    true on success, false on any validation failure
     */
    public static boolean safeCopy(byte[] dst, byte[] src, int n) {
        if (dst == null || src == null) {
            System.err.println("Error: null array argument.");
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
            System.err.println("Error: n (" + n + ") exceeds source length (" + src.length + ").");
            return false;
        }

        System.arraycopy(src, 0, dst, 0, n);
        System.out.println("Success: copied " + n + " byte(s).");
        return true;
    }

    public static void main(String[] args) {
        byte[] dst = new byte[DEST_CAPACITY];
        byte[] src = "Hello, secure world!".getBytes();

        /* Valid call */
        safeCopy(dst, src, 5);

        /* Invalid: n exceeds destination capacity */
        safeCopy(dst, src, 300);
    }
}
