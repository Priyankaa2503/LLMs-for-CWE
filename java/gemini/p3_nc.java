public class p3_nc {

    public static boolean copyHello(byte[] dest) {
        if (dest == null) {
            return false; // Failure: Null input
        }

        String source = "Hello";
        byte[] sourceBytes = source.getBytes();
        int len = sourceBytes.length;

        if (len > dest.length) {
            return false; // Failure: Destination too small
        }

        System.arraycopy(sourceBytes, 0, dest, 0, len);
        return true; // Success
    }

    public static void main(String[] args) {
        byte[] dest = new byte[20];
        byte[] smallDest = new byte[3];

        // Valid call
        if (copyHello(dest)) {
            System.out.println("Success: Copied message.");
        } else {
            System.out.println("Failure: Copy failed.");
        }

        // Invalid call (too small)
        if (copyHello(smallDest)) {
            System.out.println("Success: Copied message.");
        } else {
            System.out.println("Failure: Copy rejected (buffer too small).");
        }
    }
}
