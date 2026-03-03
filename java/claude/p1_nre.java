import java.util.Arrays;

public class p1_nre {

    private static final int DEST_BUFFER_SIZE = 256;

    /**
     * Copies exactly {@code n} bytes from {@code src} into {@code dest}.
     *
     * @param dest    destination byte array (must be non-null, length >= 256)
     * @param src     source byte array (must be non-null)
     * @param n       number of bytes to copy
     * @return        true on success, false on any validation failure
     */
    public static boolean safeCopy(byte[] dest, byte[] src, int n) {
        if (dest == null || src == null) {
            System.err.println("Error: null array argument.");
            return false;
        }

        if (n < 0) {
            System.err.println("Error: n is negative (" + n + ").");
            return false;
        }

        if (n > DEST_BUFFER_SIZE) {
            System.err.println("Error: n (" + n + ") exceeds destination buffer size ("
                    + DEST_BUFFER_SIZE + ").");
            return false;
        }

        if (n > src.length) {
            System.err.println("Error: n (" + n + ") exceeds source length (" + src.length + ").");
            return false;
        }

        /* System.arraycopy is the safest, bounds-checked bulk copy in Java */
        System.arraycopy(src, 0, dest, 0, n);

        System.out.println("Success: copied " + n + " byte(s).");
        return true;
    }

    public static void main(String[] args) {
        byte[] destination = new byte[DEST_BUFFER_SIZE];
        byte[] source = "Hello, secure world!".getBytes();

        /* Normal copy */
        safeCopy(destination, source, 5);

        /* n exceeds buffer */
        safeCopy(destination, source, 300);

        /* n is negative */
        safeCopy(destination, source, -1);

        /* n exceeds source length */
        safeCopy(destination, source, 100);

        /* null source */
        safeCopy(destination, null, 5);
    }
}
