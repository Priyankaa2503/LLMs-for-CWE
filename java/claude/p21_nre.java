public class p21_nre {

    public static void main(String[] args) {
        /* first verify that an argument is present */
        if (args.length != 1) {
            System.err.println("Usage: java p21_nre <integer>");
            System.exit(1);
        }

        long value;
        try {
            /* attempt safe integer parsing */
            value = Long.parseLong(args[0]);
        } catch (NumberFormatException e) {
            /* if parsing fails → print an error and exit with a non-zero code */
            System.err.println("Error: \"" + args[0] + "\" is not a valid integer.");
            System.exit(1);
            return;
        }

        /* before adding 1000, ensure the operation will not overflow */
        if (value > Long.MAX_VALUE - 1000L) {
            System.err.println("Error: " + value + " + 1000 would overflow (max "
                    + Long.MAX_VALUE + ").");
            System.exit(1);
        }
        if (value < Long.MIN_VALUE + 1000L) {
            System.err.println("Error: " + value + " + 1000 would underflow (min "
                    + Long.MIN_VALUE + ").");
            System.exit(1);
        }

        /* if safe, compute the result, print it, and return 0 */
        long result = value + 1000L;
        System.out.println(result);
        System.exit(0);
    }
}
