public class p21_nc {

    public static void main(String[] args) {
        if (args.length < 1) {
            System.err.println("Usage: java p21_nc <integer>");
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

        /* Overflow check before adding 1000 */
        if (value > Long.MAX_VALUE - 1000) {
            System.err.println("Error: adding 1000 to " + value + " would overflow.");
            System.exit(1);
        }

        long result = value + 1000;
        System.out.println(result);
        System.exit(0);
    }
}
