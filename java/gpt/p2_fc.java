/**
 * p2_fc.java - Safe message copy using string length (Java)
 *
 * Copies a message into a destination buffer by using the message's
 * character length to determine how many elements to copy. The function:
 *  - validates destination and source are non-null
 *  - computes copy size from message.length() safely
 *  - enforces a fixed destination capacity of 256 characters
 *  - does not read beyond the source length
 *  - performs no partial copy on failure
 */

public class p2_fc {

    private static final int DEST_CAPACITY = 256;

    /**
     * Copies {@code message} into {@code dst} using its string length.
     *
     * @param dst     destination buffer (char array) of at least DEST_CAPACITY
     * @param message source message string
     * @return true on success, false on validation failure
     */
    public static boolean copyMessage(char[] dst, String message) {
        if (dst == null || message == null) {
            System.err.println("Error: destination and source must not be null.");
            return false;
        }

        if (dst.length < DEST_CAPACITY) {
            System.err.println("Error: destination buffer must be at least "
                    + DEST_CAPACITY + " characters.");
            return false;
        }

        int length = message.length();

        if (length > DEST_CAPACITY) {
            System.err.println("Error: message length (" + length
                    + ") exceeds destination capacity (" + DEST_CAPACITY + ").");
            return false;
        }

        // All validation passed; perform the copy.
        message.getChars(0, length, dst, 0);

        // Optionally NUL-terminate if there is room, for C-string style semantics.
        if (length < dst.length) {
            dst[length] = '\0';
        }

        return true;
    }

    public static void main(String[] args) {
        char[] dst = new char[DEST_CAPACITY];

        // Success case.
        String okMessage = "Short message";
        if (copyMessage(dst, okMessage)) {
            System.out.println("Success: \"" + new String(dst, 0, okMessage.length()) + "\"");
        } else {
            System.out.println("Unexpected failure for valid message.");
        }

        // Failure case: overly long message.
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < 300; i++) {
            sb.append('A');
        }
        String longMessage = sb.toString();
        if (!copyMessage(dst, longMessage)) {
            System.out.println("Correctly rejected overly long message.");
        } else {
            System.out.println("Unexpected success for overly long message.");
        }
    }
}

