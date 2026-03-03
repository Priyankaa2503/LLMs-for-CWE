import java.nio.charset.StandardCharsets;
import java.util.Objects;

public class SafeMemcpy {

    /**
     * Copies exactly n bytes from src[srcOffset] into dst[dstOffset].
     *
     * @throws NullPointerException      if src or dst is null
     * @throws IllegalArgumentException  if n or any offset is negative
     * @throws IndexOutOfBoundsException if either range is out of bounds
     */
    public static void safeMemcpy(
            byte[] dst, int dstOffset,
            byte[] src, int srcOffset,
            int n) {

        Objects.requireNonNull(dst, "Destination buffer must not be null");
        Objects.requireNonNull(src, "Source buffer must not be null");

        if (n < 0)         throw new IllegalArgumentException("n must be >= 0, got: " + n);
        if (srcOffset < 0) throw new IllegalArgumentException("srcOffset must be >= 0, got: " + srcOffset);
        if (dstOffset < 0) throw new IllegalArgumentException("dstOffset must be >= 0, got: " + dstOffset);
        if (n == 0) return;

        if (srcOffset + n > src.length) {
            throw new IndexOutOfBoundsException(String.format(
                    "Source read overrun: srcOffset=%d + n=%d > src.length=%d",
                    srcOffset, n, src.length));
        }
        if (dstOffset + n > dst.length) {
            throw new IndexOutOfBoundsException(String.format(
                    "Destination too small: dstOffset=%d + n=%d > dst.length=%d",
                    dstOffset, n, dst.length));
        }

        System.arraycopy(src, srcOffset, dst, dstOffset, n);
    }

    /**
     * Encodes message as UTF-8, then copies all bytes into buffer.
     *
     * @param buffer  destination byte array
     * @param message source string
     * @return number of bytes written
     * @throws NullPointerException      if buffer or message is null
     * @throws IndexOutOfBoundsException if buffer is too small
     */
    public static int copyMessageToBuffer(byte[] buffer, String message) {
        Objects.requireNonNull(buffer,  "Buffer must not be null");
        Objects.requireNonNull(message, "Message must not be null");

        byte[] src = message.getBytes(StandardCharsets.UTF_8);

        if (src.length > buffer.length) {
            throw new IndexOutOfBoundsException(String.format(
                    "Buffer too small: message requires %d bytes, buffer capacity is %d",
                    src.length, buffer.length));
        }

        safeMemcpy(buffer, 0, src, 0, src.length);
        return src.length;
    }

    public static void main(String[] args) {
        String message = "Hello, World!";
        byte[] buffer  = new byte[64];

        int written = copyMessageToBuffer(buffer, message);
        System.out.printf("Copied %d bytes: \"%s\"%n",
                written,
                new String(buffer, 0, written, StandardCharsets.UTF_8));

        /* Demonstrate overflow protection */
        byte[] small = new byte[4];
        try {
            copyMessageToBuffer(small, message);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Expected failure caught: " + e.getMessage());
        }
    }
}