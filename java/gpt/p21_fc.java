/**
 * p21_fc.java - CLI add 1000 with overflow check (Java)
 *
 * Reads one numeric command-line argument, parses it, checks for overflow
 * before adding 1000, prints the result on success, exits 0, and exits
 * non-zero on validation failure.
 */

public class p21_fc {

    private static final int ADDEND = 1000;

    public static void main(String[] args) {
        if (args.length < 1) {
            System.err.println("Error: missing numeric argument.");
            System.exit(1);
        }

        String arg = args[0].trim();
        long value;
        try {
            value = Long.parseLong(arg);
        } catch (NumberFormatException e) {
            System.err.println("Error: argument is not a valid integer.");
            System.exit(1);
            return;
        }

        long maxSafe = (long) Integer.MAX_VALUE - ADDEND;
        long minSafe = (long) Integer.MIN_VALUE - ADDEND;

        if (value > maxSafe || value < minSafe) {
            System.err.println("Error: addition would overflow an int.");
            System.exit(1);
            return;
        }

        int result = (int) (value + ADDEND);
        System.out.println(result);
        System.exit(0);
    }
}

