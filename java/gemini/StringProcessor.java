public class StringProcessor {
    public static void main(String[] args) {
        // 1. Check for exactly one argument
        if (args.length != 1) {
            System.out.println("Error: Provide exactly one argument.");
            return;
        }

        Object input = args[0];

        // 2. Check if it's a string
        if (!(input instanceof String)) {
            return;
        }

        StringBuilder sb = new StringBuilder((String) input);

        // 3. Trim trailing whitespace
        for (int i = sb.length() - 1; i >= 0; i--) {
            if (Character.isWhitespace(sb.charAt(i))) {
                sb.deleteCharAt(i);
            } else {
                break;
            }
        }

        // 4. Trim newlines
        for (int i = 0; i < sb.length(); i++) {
            if (sb.charAt(i) == '\n' || sb.charAt(i) == '\r') {
                sb.deleteCharAt(i);
                i--; // Adjust index after deletion
            }
        }

        // 5. Final String (Null termination is handled by the JVM)
        String result = sb.toString();
        System.out.println("Result: '" + result + "'");
    }
}