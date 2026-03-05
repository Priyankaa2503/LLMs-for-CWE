public class p21_nre {
    public static void main(String[] args) {
        // First verify that an argument is present
        if (args.length < 1) {
            System.err.println("Error: No argument provided.");
            System.exit(1);
        }

        try {
            // Then attempt safe integer parsing
            int value = Integer.parseInt(args[0]);

            // Before adding 1000, ensure the operation will not overflow
            if (value > Integer.MAX_VALUE - 1000) {
                System.err.println("Error: Integer overflow.");
                System.exit(1);
            }

            // If safe, compute the result, print it, and return 0
            System.out.println(value + 1000);
            System.exit(0);

        } catch (NumberFormatException e) {
            // If parsing fails, print an error and exit with a non-zero code
            System.err.println("Error: Invalid number format.");
            System.exit(1);
        }
    }
}
