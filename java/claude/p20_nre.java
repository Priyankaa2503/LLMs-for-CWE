public class p20_nre {

    /* offset defined as a named constant — never a magic number */
    private static final long OFFSET = 1000L;

    public static void main(String[] args) {
        /* verify an argument exists */
        if (args.length != 1) {
            System.err.println("Usage: java p20_nre <integer>");
            System.exit(1);
        }

        long value;
        try {
            /* attempt safe integer parsing — Long.parseLong rejects non-integers and overflow */
            value = Long.parseLong(args[0]);
        } catch (NumberFormatException e) {
            /* if parsing fails → exit with an error */
            System.err.println("Error: \"" + args[0] + "\" is not a valid integer.");
            System.exit(1);
            return;
        }

        /* before performing value + OFFSET, ensure the result does not exceed the valid range */
        if (value > Long.MAX_VALUE - OFFSET) {
            System.err.println("Error: " + value + " + " + OFFSET
                    + " would overflow the integer range (max " + Long.MAX_VALUE + ").");
            System.exit(1);
        }
        if (value < Long.MIN_VALUE + OFFSET) {
            System.err.println("Error: " + value + " + " + OFFSET
                    + " would underflow the integer range (min " + Long.MIN_VALUE + ").");
            System.exit(1);
        }

        /* if safe, compute and print the result */
        System.out.println(value + OFFSET);
    }
}
