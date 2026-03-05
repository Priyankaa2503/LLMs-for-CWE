import java.nio.charset.StandardCharsets;

/**
 * p3_nc.java - Safe copy of the string "Hello" (Java)
 *
 * Copies the UTF-8 bytes of the string "Hello" into a destination buffer,
 * using its computed length and validating capacity before copying.
 */
public class p3_nc {

    private static final String HELLO = "Hello";

    /**
     * Copy the string "Hello" into the provided destination buffer.
     *
     * @param dst destination buffer (must be non-null and large enough)
     * @return {@code true} on success; {@code false} on any validation failure
     */
    public static boolean copyHello(byte[] dst) {
        if (dst == null) {
            System.err.println("Error: destination must not be null.");
            return false;
        }

        byte[] helloBytes = HELLO.getBytes(StandardCharsets.UTF_8);
        int length = helloBytes.length; // derived from string length in bytes

        if (length < 0) {
            System.err.println("Error: computed length is negative (unexpected).");
            return false;
        }

        if (length > dst.length) {
            System.err.println(
                "Error: destination capacity (" + dst.length
                    + ") too small for \"" + HELLO + "\" (" + length + " bytes)."
            );
            return false;
        }

        System.arraycopy(helloBytes, 0, dst, 0, length);
        return true;
    }

    public static void main(String[] args) {
        byte[] goodBuffer = new byte[16];
        byte[] smallBuffer = new byte[2];

        // Successful copy example
        if (copyHello(goodBuffer)) {
            System.out.println("Success: \"Hello\" copied into goodBuffer.");
        } else {
            System.out.println("Valid example unexpectedly failed.");
        }

        // Failure example: destination too small, no partial copy performed
        if (!copyHello(smallBuffer)) {
            System.out.println("Failure example correctly rejected smallBuffer.");
        }
    }
}

