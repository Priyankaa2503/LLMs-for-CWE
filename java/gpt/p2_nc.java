import java.nio.charset.StandardCharsets;

/**
 * p2_nc.java - Safe message-to-buffer copy using string length (Java)
 *
 * Copies bytes from a source message into a destination buffer, using the
 * encoded byte length of the string as the copy length.
 */
public class p2_nc {

    private static final int DEST_CAPACITY = 256;

    /**
     * Copy bytes from {@code msg} into {@code dst} using its encoded length.
     *
     * @param msg source message string (must be non-null)
     * @param dst destination buffer (must be non-null, length >= 1)
     * @return {@code true} on success; {@code false} if validation fails
     */
    public static boolean copyMessageToBuffer(String msg, byte[] dst) {
        if (msg == null || dst == null) {
            System.err.println("Error: message and destination must not be null.");
            return false;
        }

        if (dst.length <= 0) {
            System.err.println("Error: destination capacity must be positive.");
            return false;
        }

        byte[] msgBytes = msg.getBytes(StandardCharsets.UTF_8);
        int copyLen = msgBytes.length; // derived from the string's byte length

        if (copyLen < 0) {
            System.err.println("Error: computed length is negative (unexpected).");
            return false;
        }

        if (copyLen > DEST_CAPACITY || copyLen > dst.length) {
            System.err.println(
                "Error: message length (" + copyLen + ") exceeds destination capacity ("
                    + Math.min(DEST_CAPACITY, dst.length) + ")."
            );
            return false;
        }

        System.arraycopy(msgBytes, 0, dst, 0, copyLen);
        return true;
    }

    public static void main(String[] args) {
        byte[] dst = new byte[DEST_CAPACITY];

        // Successful copy example
        if (copyMessageToBuffer("Hello, secure world!", dst)) {
            System.out.println("Success: copied message bytes.");
        } else {
            System.out.println("Valid example unexpectedly failed.");
        }

        // Failure example: destination too small for message
        byte[] smallDst = new byte[8];
        if (!copyMessageToBuffer("This message is too long for 8 bytes", smallDst)) {
            System.out.println("Failure example correctly rejected oversize copy.");
        }
    }
}

