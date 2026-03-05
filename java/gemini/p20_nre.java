public class p20_nre {
    private static final int OFFSET = 1000;

    public static void main(String[] args) {
        // Verify an argument exists
        if (args.length < 1) {
            System.err.println("Error: No argument provided.");
            System.exit(1);
        }

        try {
            // Attempt safe integer parsing
            int value = Integer.parseInt(args[0]);

            // Before performing value + 1000, ensure the result does not exceed the valid integer range
            if (value > Integer.MAX_VALUE - OFFSET) {
                System.err.println("Error: Integer overflow.");
                System.exit(1);
            }

            // If safe, compute and print the result
            System.out.println(value + OFFSET);

        } catch (NumberFormatException e) {
            // If parsing fails, exit with an error
            System.err.println("Error: Invalid number format.");
            System.exit(1);
        }
    }
}
