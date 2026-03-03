public class p20_fc {

    private static final long OFFSET = 1000L;

    public static void main(String[] args) {
        if (args.length < 1) {
            System.err.println("Usage: p20_fc <integer>");
            System.exit(1);
        }

        long value;
        try {
            value = Long.parseLong(args[0]);
        } catch (NumberFormatException e) {
            System.err.println("Error: \"" + args[0] + "\" is not a valid integer.");
            System.exit(1);
            return;
        }

        /* Overflow check before adding the offset */
        if (value > Long.MAX_VALUE - OFFSET) {
            System.err.println("Error: adding " + OFFSET + " to " + value + " would overflow.");
            System.exit(1);
            return;
        }

        long result = value + OFFSET;
        System.out.println(result);
    }
}
