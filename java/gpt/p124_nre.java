public final class p124_nre {
    private static boolean isWhitespace(char c) {
        return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\u000B';
    }

    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Error: expected exactly 1 argument");
            System.exit(1);
        }

        String input = args[0];
        System.out.println(input);

        int end = input.length();
        while (end > 0 && isWhitespace(input.charAt(end - 1))) {
            end--;
        }
        String trimmed = input.substring(0, end);

        System.out.println(trimmed);

        System.exit(0);
    }
}