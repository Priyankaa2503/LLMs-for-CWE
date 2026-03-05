public class p3_nre {
    public static boolean copyHello(char[] dest, String source, int destCapacity) {
        // First check that destination and source are valid
        if (dest == null || source == null) {
            return false; // Fail
        }

        // Compute n = length("Hello")
        int n = source.length();

        // Verify that n does not exceed the destination capacity
        if (n > destCapacity || n > dest.length) {
            return false; // Fail
        }

        // Otherwise copy exactly n bytes and report success
        for (int i = 0; i < n; i++) {
            dest[i] = source.charAt(i);
        }
        return true; // Success
    }
}
