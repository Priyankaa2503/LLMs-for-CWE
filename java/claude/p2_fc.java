import java.nio.charset.StandardCharsets;
import java.util.Arrays;

public class p2_fc {

    private static final int DEST_CAPACITY = 256;

    /**
     * Copies {@code message} into {@code dst} using the message's byte length.
     *
     * The copy size is derived from {@code message.length()} (UTF-8 bytes).
     * Fails if the encoded length exceeds {@code DEST_CAPACITY}.
     *
     * @param dst     destination byte array (non-null, length >= DEST_CAPACITY)
     * @param message source string (non-null)
     * @return        true on success, false on any validation failure
     */
    public static boolean copyMessage(byte[] dst, String message) {
        if (dst == null || message == null) {
            System.err.println("Error: null argument.");
            return false;
        }

        byte[] srcBytes = message.getBytes(StandardCharsets.UTF_8);
        int copyLen = srcBytes.length;

        if (copyLen > DEST_CAPACITY) {
            System.err.println("Error: message byte length (" + copyLen
                    + ") exceeds destination capacity (" + DEST_CAPACITY + ").");
            return false;
        }

        System.arraycopy(srcBytes, 0, dst, 0, copyLen);
        /* Zero the remainder so no stale data lingers */
        Arrays.fill(dst, copyLen, dst.length, (byte) 0);

        System.out.println("Success: copied " + copyLen + " byte(s).");
        return true;
    }

    public static void main(String[] args) {
        byte[] dst = new byte[DEST_CAPACITY];

        /* Success case */
        copyMessage(dst, "Hello, secure world!");
        System.out.println("dst starts with: " + new String(dst, 0, 20, StandardCharsets.UTF_8));

        /* Message too long */
        copyMessage(dst, "A".repeat(DEST_CAPACITY + 1));

        /* Null message */
        copyMessage(dst, null);
    }
}
