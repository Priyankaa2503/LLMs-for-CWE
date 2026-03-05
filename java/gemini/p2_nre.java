public class p2_nre {
    public static boolean copyMessage(char[] dest, String message, int destCapacity) {
        // First check destination and source are valid
        if (dest == null || message == null) {
            return false; // Fail
        }

        // Compute n = length(message) safely
        int n = message.length();

        // Verify n is within the destination’s capacity
        if (n > destCapacity || n > dest.length) {
            return false; // Fail
        }

        // Otherwise copy exactly n bytes and report success
        // Copy characters from string to char array
        for (int i = 0; i < n; i++) {
            dest[i] = message.charAt(i);
        }
        return true; // Success
    }
}
