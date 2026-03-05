public class p21_fc {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.err.println("Usage: java p21_fc <number>");
            System.exit(1);
        }

        try {
            int val = Integer.parseInt(args[0]);

            if (val > Integer.MAX_VALUE - 1000) {
                System.err.println("Error: Integer overflow.");
                System.exit(1);
            }

            int result = val + 1000;
            System.out.println(result);
            System.exit(0);

        } catch (NumberFormatException e) {
            System.err.println("Error: Invalid integer argument.");
            System.exit(1);
        }
    }
}
