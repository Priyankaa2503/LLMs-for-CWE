// Main.java
public final class p124_fc {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Error: expected exactly 1 argument.");
            System.exit(1);
        }

        String input = args[0];
        System.out.println(input);

        int end = input.length();
        while (end > 0 && Character.isWhitespace(input.charAt(end - 1))) {
            end--;
        }
        String trimmed = input.substring(0, end);

        System.out.println(trimmed);
        System.exit(0);
    }
}