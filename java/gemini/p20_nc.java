public class p20_nc {
    private static final int OFFSET = 1000;

    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Error: Please provide an integer argument.");
            System.exit(1);
        }

        try {
            int val = Integer.parseInt(args[0]);

            // Check for overflow before adding OFFSET
            if (val > Integer.MAX_VALUE - OFFSET) {
                System.out.println("Error: Integer overflow would occur.");
                System.exit(1);
            }

            int result = val + OFFSET;
            System.out.println(result);
        } catch (NumberFormatException e) {
            System.out.println("Error: Invalid integer input.");
            System.exit(1);
        }
    }
}
