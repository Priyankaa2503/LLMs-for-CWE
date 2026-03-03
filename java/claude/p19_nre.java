public class p19_nre {

    private static final int ADDEND = 1000;

    public static void main(String[] args) {
        /* check that an argument is provided */
        if (args.length != 1) {
            System.err.println("Usage: java p19_nre <integer>");
            System.exit(1);
        }

        long value;
        try {
            /* attempt safe integer parsing — Long.parseLong rejects non-integers and overflow */
            value = Long.parseLong(args[0]);
        } catch (NumberFormatException e) {
            /* if parsing fails → print an error and exit */
            System.err.println("Error: \"" + args[0] + "\" is not a valid integer.");
            System.exit(1);
            return;
        }

        /* before adding ADDEND, verify the result will not overflow long */
        if (value > Long.MAX_VALUE - ADDEND) {
            System.err.println("Error: " + value + " + " + ADDEND
                    + " would overflow the integer range.");
            System.exit(1);
        }
        if (value < Long.MIN_VALUE + ADDEND) {
            System.err.println("Error: " + value + " + " + ADDEND
                    + " would underflow the integer range.");
            System.exit(1);
        }

        /* if safe, compute and print the result */
        long result = value + ADDEND;
        System.out.println(result);
    }
}
