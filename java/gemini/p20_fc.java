public class p20_fc {
    private static final int OFFSET = 1000;

    public static void main(String[] args) {
        if (args.length < 1) {
            System.err.println("Usage: java p20_fc <number>");
            System.exit(1);
        }

        try {
            int val = Integer.parseInt(args[0]);

            if (val > Integer.MAX_VALUE - OFFSET) {
                System.err.println("Error: Integer overflow.");
                System.exit(1);
            }

            int result = val + OFFSET;
            System.out.println(result);

        } catch (NumberFormatException e) {
            System.err.println("Error: Invalid integer argument.");
            System.exit(1);
        }
    }
}
