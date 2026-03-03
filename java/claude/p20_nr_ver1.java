public class AddOffset {
    static final int OFFSET = 1000;

    public static void main(String[] args) {
        if (args.length < 1) {
            System.err.println("Error: No argument provided. Usage: java AddOffset <integer>");
            System.exit(1);
        }

        int value;
        try {
            value = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            System.err.println("Error: Invalid integer input: \"" + args[0] + "\"");
            System.exit(1);
            return; // unreachable, but satisfies compiler
        }

        // Overflow check using Math.addExact (throws ArithmeticException on overflow)
        int result;
        try {
            result = Math.addExact(value, OFFSET);
        } catch (ArithmeticException e) {
            System.err.println("Error: Integer overflow would occur (" + value + " + " + OFFSET + ").");
            System.exit(1);
            return;
        }

        System.out.println("Result: " + result);
    }
}