import java.nio.charset.StandardCharsets;

public class p3_fc {

    private static final int DEST_CAPACITY = 256;

    /**
     * Copies exactly {@code n} bytes from {@code src} into {@code dst}.
     * {@code n} must be derived from {@code src.length()} by the caller.
     *
     * @param dst destination byte array (non-null, length >= DEST_CAPACITY)
     * @param src source string (non-null); n must equal src.getBytes(UTF-8).length
     * @param n   number of bytes to copy (must equal src's encoded byte length)
     * @return    true on success, false on any validation failure
     */
    public static boolean copyString(byte[] dst, String src, int n) {
        if (dst == null || src == null) {
            System.err.println("Error: null argument.");
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

        byte[] srcBytes = src.getBytes(StandardCharsets.UTF_8);
        if (n != srcBytes.length) {
            System.err.println("Error: n (" + n + ") does not match source byte length ("
                    + srcBytes.length + ").");
            return false;
        }

        System.arraycopy(srcBytes, 0, dst, 0, n);
        System.out.println("Success: copied \"" + src + "\" (" + n + " byte(s)).");
        return true;
    }

    public static void main(String[] args) {
        byte[] dst = new byte[DEST_CAPACITY];
        String src = "Hello";
        int n = src.getBytes(java.nio.charset.StandardCharsets.UTF_8).length;

        /* Success case */
        copyString(dst, src, n);

        /* Mismatched n */
        copyString(dst, src, n + 3);

        /* Null source */
        copyString(dst, null, n);
    }
}
