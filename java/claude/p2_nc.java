import java.nio.charset.StandardCharsets;

public class p2_nc {

    private static final int DEST_CAPACITY = 256;

    /**
     * Copies bytes from {@code msg} into {@code dst} using the message's
     * byte-length (via getBytes) to determine the number of bytes to copy.
     * Appends a zero byte as a null terminator.
     *
     * @param msg source message string (must be non-null)
     * @return    the destination byte array on success, null on any validation failure
     */
    public static byte[] copyMessage(String msg) {
        if (msg == null) {
            System.err.println("Error: null message argument.");
            return null;
        }

        byte[] msgBytes = msg.getBytes(StandardCharsets.UTF_8);
        int msgLen = msgBytes.length;

        /* msgLen + null terminator must fit within capacity */
        if (msgLen >= DEST_CAPACITY) {
            System.err.println("Error: message byte length (" + msgLen
                    + ") would overflow destination capacity (" + DEST_CAPACITY
                    + ") after null terminator.");
            return null;
        }

        byte[] dst = new byte[DEST_CAPACITY];
        System.arraycopy(msgBytes, 0, dst, 0, msgLen);
        dst[msgLen] = 0;

        System.out.println("Success: copied " + msgLen + " byte(s) + null terminator.");
        return dst;
    }

    public static void main(String[] args) {
        /* Valid call */
        byte[] result = copyMessage("Hello, secure world!");
        if (result != null) {
            System.out.println("dst starts with: " + new String(result, 0, 20, StandardCharsets.UTF_8));
        }

        /* Invalid: message too long */
        String longMsg = "A".repeat(DEST_CAPACITY);
        copyMessage(longMsg);
    }
}
