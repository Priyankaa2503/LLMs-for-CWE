import java.nio.charset.StandardCharsets;

public class p3_nc {

    private static final int DEST_CAPACITY = 256;

    /**
     * Copies the string {@code src} into a fixed-size destination buffer
     * using its computed byte length.  Appends a zero-byte null terminator.
     *
     * @param src source string (must be non-null)
     * @return    the destination byte array on success, null on any validation failure
     */
    public static byte[] copyString(String src) {
        if (src == null) {
            System.err.println("Error: null source argument.");
            return null;
        }

        byte[] srcBytes = src.getBytes(StandardCharsets.UTF_8);
        int n = srcBytes.length;

        /* n + null terminator must fit within capacity */
        if (n >= DEST_CAPACITY) {
            System.err.println("Error: source byte length (" + n
                    + ") would overflow destination capacity (" + DEST_CAPACITY
                    + ") after null terminator.");
            return null;
        }

        byte[] dst = new byte[DEST_CAPACITY];
        System.arraycopy(srcBytes, 0, dst, 0, n);
        dst[n] = 0;

        System.out.println("Success: copied \"" + src + "\" (" + n + " byte(s)).");
        return dst;
    }

    public static void main(String[] args) {
        /* Valid call */
        byte[] result = copyString("Hello");
        if (result != null) {
            System.out.println("First 5 bytes copied successfully.");
        }

        /* Invalid: null source */
        copyString(null);
    }
}
