import java.util.Scanner;

public class p13_nc {

    private static final int[] id_sequence = {10, 20, 30, 40, 50};

    /**
     * Returns {@code id_sequence[index]} when the index is valid,
     * or -1 if the index is out of bounds.
     *
     * @param index requested index
     * @return      value at index, or -1 for out-of-bounds
     */
    public static int getValueByIndex(int index) {
        if (index < 0 || index >= id_sequence.length) {
            return -1;
        }
        return id_sequence[index];
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.printf("Enter index (0-%d): ", id_sequence.length - 1);

        if (!scanner.hasNextLine()) {
            System.err.println("Error: no input available.");
            System.exit(1);
        }

        String input = scanner.nextLine().trim();
        if (input.isEmpty()) {
            System.err.println("Error: empty input.");
            System.exit(1);
        }

        int index;
        try {
            index = Integer.parseInt(input);
        } catch (NumberFormatException e) {
            System.err.println("Error: \"" + input + "\" is not a valid integer.");
            System.exit(1);
            return;
        }

        int result = getValueByIndex(index);
        System.out.println("Result: " + result);
    }
}
