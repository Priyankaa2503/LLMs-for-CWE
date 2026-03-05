public class p20_nre {
    private static final long OFFSET = 1000L;

    public static void main(String[] args) {
        if (args.length < 1) {
            System.err.println("Missing argument");
            System.exit(1);
            return;
        }

        long val;
        try {
            val = Long.parseLong(args[0]);
        } catch (NumberFormatException ex) {
            System.err.println("Invalid number");
            System.exit(1);
            return;
        }

        long result = val + OFFSET;
        if (result > Integer.MAX_VALUE || result < Integer.MIN_VALUE) {
            System.err.println("Overflow risk");
            System.exit(1);
            return;
        }

        System.out.println(result);
        System.exit(0);
    }
}
