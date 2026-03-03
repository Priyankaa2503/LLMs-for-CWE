public class AddThousand {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.err.println("Error: No argument provided. Usage: java AddThousand <integer>");
            System.exit(1);
        }

        long value;
        try {
            value = Long.parseLong(args[0]);
        } catch (NumberFormatException e) {
            System.err.println("Error: Invalid integer: '" + args[0] + "'");
            System.exit(1);
            return;
        }

        // Overflow check before adding 1000
        if (value > Long.MAX_VALUE - 1000) {
            System.err.println("Error: Integer overflow would occur.");
            System.exit(1);
        }

        value += 1000;
        System.out.println(value);
        System.exit(0);
    }
}