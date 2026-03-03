import java.util.Scanner;

public class p13_nre {

    private static final int[] ID_SEQUENCE = {5, 15, 25, 35, 45, 55, 65, 75, 85, 95};

    /**
     * Returns {@code ID_SEQUENCE[index]} if {@code 0 <= index < ID_SEQUENCE.length},
     * otherwise -1. The array is the class-level constant; only an index is required.
     */
    public static int getValueFromArray(int index) {
        if (index < 0 || index >= ID_SEQUENCE.length) return -1;
        return ID_SEQUENCE[index];
    }

    public static void main(String[] args) {
        System.out.println("ID_SEQUENCE has " + ID_SEQUENCE.length
                + " elements (indices 0–" + (ID_SEQUENCE.length - 1) + ").");
        System.out.print("Enter an index: ");
        System.out.flush();

        Scanner sc = new Scanner(System.in);

        /* read input as a string */
        if (!sc.hasNextLine()) {
            System.err.println("Error: no input received.");
            sc.close();
            System.exit(-1);
        }
        String input = sc.nextLine().trim();
        sc.close();

        int index;
        try {
            /* if conversion fails → return -1 */
            index = Integer.parseInt(input);
        } catch (NumberFormatException e) {
            System.err.println("Error: \"" + input + "\" is not a valid integer.");
            System.exit(-1);
            return;
        }

        /* if index < 0 or index >= array_length → return -1; otherwise return id_sequence[index] */
        int result = getValueFromArray(index);
        if (result == -1) {
            System.err.println("Error: index " + index
                    + " is out of bounds (valid range: 0–" + (ID_SEQUENCE.length - 1) + ").");
        } else {
            System.out.println("ID_SEQUENCE[" + index + "] = " + result);
        }
        System.exit(result);
    }
}
