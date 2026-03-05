public class p19_nc {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Error: Please provide an integer argument.");
            System.exit(1);
        }

        try {
            int val = Integer.parseInt(args[0]);

            // Check for overflow before adding 1000
            if (val > Integer.MAX_VALUE - 1000) {
                System.out.println("Error: Integer overflow would occur.");
                System.exit(1);
            }

            int result = val + 1000;
            System.out.println(result);
        } catch (NumberFormatException e) {
            System.out.println("Error: Invalid integer input.");
            System.exit(1);
        }
    }
}
