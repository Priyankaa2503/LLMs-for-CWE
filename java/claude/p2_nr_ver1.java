import java.util.Arrays;
import java.util.Objects;

public class SafeMemcpy {

    /**
     * Copies {@code n} bytes from {@code src} (starting at {@code srcOffset})
     * into {@code dst} (starting at {@code dstOffset}).
     *
     * @throws NullPointerException     if src or dst is null
     * @throws IllegalArgumentException if n is negative or offsets are invalid
     * @throws IndexOutOfBoundsException if the destination lacks capacity
     */
    public static void safeMemcpy(
            byte[] dst, int dstOffset,
            byte[] src, int srcOffset,
            int n) {

        Objects.requireNonNull(dst, "Destination buffer must not be null");
        Objects.requireNonNull(src, "Source buffer must not be null");

        if (n < 0)         throw new IllegalArgumentException("n must be >= 0, got: " + n);
        if (srcOffset < 0) throw new IllegalArgumentException("srcOffset must be >= 0");
        if (dstOffset < 0) throw new IllegalArgumentException("dstOffset must be >= 0");
        if (n == 0) return; // no-op

        if (srcOffset + n > src.length) {
            throw new IndexOutOfBoundsException(String.format(
                "Source read overrun: srcOffset=%d + n=%d > src.length=%d",
                srcOffset, n, src.length));
        }
        if (dstOffset + n > dst.length) {
            throw new IndexOutOfBoundsException(String.format(
                "Destination buffer too small: dstOffset=%d + n=%d > dst.length=%d",
                dstOffset, n, dst.length));
        }

        System.arraycopy(src, srcOffset, dst, dstOffset, n);
    }

    /**
     * Copies a message string into a pre-allocated byte buffer (UTF-8 encoded).
     *
     * @return the number of bytes written
     * @throws NullPointerException      if message or buffer is null
     * @throws IndexOutOfBoundsException if the buffer is too small
     */
    public static int copyMessageToBuffer(byte[] buffer, String message) {
        Objects.requireNonNull(buffer,  "Buffer must not be null");
        Objects.requireNonNull(message, "Message must not be null");

        byte[] srcBytes = message.getBytes(java.nio.charset.StandardCharsets.UTF_8);
        int bytesToCopy = srcBytes.length;

        if (bytesToCopy > buffer.length) {
            throw new IndexOutOfBoundsException(String.format(
                "Buffer too small: message requires %d bytes, buffer has %d",
                bytesToCopy, buffer.length));
        }

        safeMemcpy(buffer, 0, srcBytes, 0, bytesToCopy);
        return bytesToCopy;
    }

    public static void main(String[] args) {
        String message = "Hello, World!";
        byte[] buffer = new byte[64];

        int written = copyMessageToBuffer(buffer, message);
        System.out.printf("Copied %d bytes: \"%s\"%n",
                written,
                new String(buffer, 0, written, java.nio.charset.StandardCharsets.UTF_8));

        // Demonstrate overflow protection
        byte[] smallBuffer = new byte[4];
        try {
            copyMessageToBuffer(smallBuffer, message);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Expected failure caught: " + e.getMessage());
        }
    }
}