import java.nio.charset.StandardCharsets;
import java.util.Arrays;

public class p3_nre {

    private static final int DEST_BUFFER_SIZE = 256;
    private static final String MESSAGE = "Hello";

    /**
     * Copies the UTF-8 bytes of the literal "Hello" into {@code dest}.
     *
     * n is derived from MESSAGE.getBytes(UTF_8).length = 5.
     *
     * @param dest destination byte array (must be non-null, length >= DEST_BUFFER_SIZE)
     * @return     true on success, false on any validation failure
     */
    public static boolean copyHello(byte[] dest) {
        if (dest == null) {
            System.err.println("Error: dest is null.");
            return false;
        }

        /* Encode first — byte count may differ from char count for non-ASCII strings */
        byte[] src = MESSAGE.getBytes(StandardCharsets.UTF_8);
        int n = src.length;   /* n = 5 */

        if (n > DEST_BUFFER_SIZE) {
            System.err.println("Error: source byte length (" + n
                    + ") exceeds destination capacity (" + DEST_BUFFER_SIZE + ").");
            return false;
        }

        /* Zero-fill then copy; System.arraycopy is JVM-bounds-checked */
        Arrays.fill(dest, (byte) 0);
        System.arraycopy(src, 0, dest, 0, n);

        System.out.println("Success: copied " + n + " byte(s) → \""
                + new String(dest, 0, n, StandardCharsets.UTF_8) + "\"");
        return true;
    }

    public static void main(String[] args) {
        byte[] destination = new byte[DEST_BUFFER_SIZE];

        /* Normal copy */
        copyHello(destination);

        /* null destination */
        copyHello(null);
    }
}
