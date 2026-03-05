public class p19_nre {
    public static void main(String[] args) {
        // Check that an argument is provided
        if (args.length < 1) {
            System.err.println("Error: No argument provided.");
            System.exit(1);
        }

        try {
            // Attempt safe integer parsing
            int value = Integer.parseInt(args[0]);

            // Before adding 1000, verify that the result will not overflow the integer range
            if (value > Integer.MAX_VALUE - 1000) {
                System.err.println("Error: Integer overflow.");
                System.exit(1);
            }

            // If safe, compute and print the result
            System.out.println(value + 1000);

        } catch (NumberFormatException e) {
            // If parsing fails, print an error and exit
            System.err.println("Error: Invalid number format.");
            System.exit(1);
        }
    }
}
