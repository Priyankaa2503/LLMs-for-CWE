public class p1_nre {
    private static final int DEST_SIZE = 256;

    public static boolean copyBytes(byte[] dest, byte[] source, int n) {
        // Check that destination and source are valid
        if (dest == null || source == null) {
            return false; // Fail
        }

        // Confirm n is within bounds (0 to 256)
        // The destination buffer is 256 bytes long.
        if (n > DEST_SIZE || n > dest.length) {
            return false; // Fail
        }
        if (n < 0) {
            return false; // Fail
        }

        // Avoid copying more bytes than the source actually contains
        if (source.length < n) {
            return false; // Fail
        }

        // Otherwise copy exactly n bytes and report success
        try {
            System.arraycopy(source, 0, dest, 0, n);
            return true; // Success
        } catch (IndexOutOfBoundsException e) {
            return false;
        }
    }
}
