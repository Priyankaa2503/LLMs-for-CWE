public class p1_nc {
    private static final int DEST_SIZE = 256;

    public static boolean copyBytes(byte[] source, byte[] dest, int n) {
        if (source == null || dest == null) {
            return false; // Failure: Null array
        }
        if (n < 0) {
            return false; // Failure: Negative count
        }
        if (n > DEST_SIZE) {
            return false; // Failure: Exceeds destination buffer size
        }
        if (n > dest.length) { // Check actual dest length too, though prompt says dest is always 256
             return false;
        }
        if (n > source.length) {
            return false; // Failure: Exceeds source length
        }

        System.arraycopy(source, 0, dest, 0, n);
        return true; // Success
    }

    public static void main(String[] args) {
        byte[] source = "This is a test string.".getBytes();
        byte[] dest = new byte[DEST_SIZE];

        // Valid call
        if (copyBytes(source, dest, 10)) {
            System.out.println("Success: Copied 10 bytes.");
        } else {
            System.out.println("Failure: Copy failed.");
        }

        // Invalid call (n too large)
        if (copyBytes(source, dest, 300)) {
            System.out.println("Success: Copied 300 bytes.");
        } else {
            System.out.println("Failure: Copy failed cleanly (n too large).");
        }
    }
}
