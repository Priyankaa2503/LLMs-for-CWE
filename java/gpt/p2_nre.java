import java.nio.charset.StandardCharsets;

public class p2_nre {
    /** Returns 0 on success, -1 on validation failure */
    public static int copyMessage(byte[] dest, String message) {
        if (dest == null || message == null) {
            return -1;
        }

        byte[] msgBytes = message.getBytes(StandardCharsets.UTF_8);
        int n = msgBytes.length;

        if (n < 0 || n >= dest.length) { // reserve space for a terminator-equivalent if needed
            return -1;
        }

        System.arraycopy(msgBytes, 0, dest, 0, n);
        dest[n] = 0; // explicit terminator for parity with C-style handling
        return 0;
    }
}
