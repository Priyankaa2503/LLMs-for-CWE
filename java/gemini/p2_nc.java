public class p2_nc {

    public static boolean copyMessage(String source, byte[] dest) {
        if (source == null || dest == null) {
            return false; // Failure: Null input
        }

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
        String msg1 = "Hello World";
        String msg2 = "This message is way too long for the buffer";

        // Valid call
        if (copyMessage(msg1, dest)) {
            System.out.println("Success: Copied message.");
        } else {
            System.out.println("Failure: Copy failed.");
        }

        // Invalid call (too long)
        if (copyMessage(msg2, dest)) {
            System.out.println("Success: Copied message.");
        } else {
            System.out.println("Failure: Copy rejected (too long).");
        }
    }
}
