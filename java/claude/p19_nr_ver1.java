public class Solution {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.err.println("Error: No argument provided. Usage: java Solution <number>");
            System.exit(1);
        }

        long value;
        try {
            value = Long.parseLong(args[0]);
        } catch (NumberFormatException e) {
            System.err.println("Error: '" + args[0] + "' is not a valid integer.");
            System.exit(1);
            return;
        }

        // Check overflow against Long bounds
        if (value > Long.MAX_VALUE - 1000) {
            System.err.println("Error: Input too large; adding 1000 would overflow.");
            System.exit(1);
        }
        if (value < Long.MIN_VALUE + 1000) {
            System.err.println("Error: Input too small; adding 1000 would underflow.");
            System.exit(1);
        }

        long result = value + 1000;
        System.out.println(value + " + 1000 = " + result);
    }
}