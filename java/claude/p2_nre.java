import java.nio.charset.StandardCharsets;
import java.util.Arrays;

public class p2_nre {

    private static final int DEST_BUFFER_SIZE = 256;

    /**
     * Copies the UTF-8 bytes of {@code message} into {@code dest}.
     *
     * n is derived from message.getBytes(UTF_8).length inside the method.
     *
     * @param dest    destination byte array (length >= DEST_BUFFER_SIZE)
     * @param message source string (must be non-null)
     * @return        true on success, false on any validation failure
     */
    public static boolean safeCopy(byte[] dest, String message) {
        if (dest == null) {
            System.err.println("Error: dest is null.");
            return false;
        }

        if (message == null) {
            System.err.println("Error: message is null.");
            return false;
        }

        /* Encode first so n reflects the true byte count (handles multi-byte chars) */
        byte[] src = message.getBytes(StandardCharsets.UTF_8);
        int n = src.length;

        if (n > DEST_BUFFER_SIZE) {
            System.err.println("Error: message byte length (" + n
                    + ") exceeds destination capacity (" + DEST_BUFFER_SIZE + ").");
            return false;
        }

        /* System.arraycopy is bounds-checked by the JVM */
        Arrays.fill(dest, (byte) 0);
        System.arraycopy(src, 0, dest, 0, n);

        System.out.println("Success: copied " + n + " byte(s) → \""
                + new String(dest, 0, n, StandardCharsets.UTF_8) + "\"");
        return true;
    }

    public static void main(String[] args) {
        byte[] destination = new byte[DEST_BUFFER_SIZE];

        /* Normal copy */
        safeCopy(destination, "Hello, secure world!");

        /* Empty string edge case */
        safeCopy(destination, "");

        /* null message */
        safeCopy(destination, null);

        /* null dest */
        safeCopy(null, "Hello");

        /* Message too long */
        safeCopy(destination, "A".repeat(260));
    }
}
