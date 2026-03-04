public class Main {
    public static void main(String[] args) {
        // 1. Check for exactly one argument
        if (args.length != 1) {
            System.out.println("Error: Please provide exactly one argument.");
            System.exit(1);
        }

        // 2. Store the argument
        String input = args[0];

        // 3. Print the argument
        System.out.println("Original: '" + input + "'");

        // 4. Trim trailing whitespace
        input = input.replaceAll("\\s+$", ""); 

        // 5. Print again
        System.out.println("Trimmed:  '" + input + "'");

        // 6. Exit
        System.exit(0);
    }
}