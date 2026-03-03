import java.util.Arrays;
public final class SafeMemCopy {
    /** Fixed destination buffer size. */
    public static final int DEST_BUFFER_SIZE = 256;
    private SafeMemCopy() {} // utility class — no instances
    /**
     * Copies {@code count} bytes from {@code src} (starting at index 0)
     * into a newly allocated 256-byte destination buffer.
     *
     * @param src   source byte array (must not be null)
     * @param count number of bytes to copy (0 – 256, must not exceed src.length)
     * @return a 256-byte destination buffer containing the copied bytes
     * @throws IllegalArgumentException if any argument is invalid
     */
    public static byte[] safeCopy(byte[] src, int count) {
        // 1. Null check
        if (src == null) {
            throw new IllegalArgumentException(
                "src must not be null");
        }
        // 2. Negative count
        if (count < 0) {
            throw new IllegalArgumentException(
                "count must not be negative: " + count);
        }
        // 3. Destination overflow
        if (count > DEST_BUFFER_SIZE) {
            throw new IllegalArgumentException(
                "count (" + count + ") exceeds destination buffer "
                + "size (" + DEST_BUFFER_SIZE + ")");
        }
        // 4. Source overread
        if (count > src.length) {
            throw new IllegalArgumentException(
                "count (" + count + ") exceeds source length "
                + "(" + src.length + ")");
        }
        // 5. Allocate fixed-size dest and copy
        byte[] dest = new byte[DEST_BUFFER_SIZE];
        System.arraycopy(src, 0, dest, 0, count);
        return dest;
    }
}