import java.util.Scanner;

public class p10_nre {

    /**
     * Returns the element at {@code index} in {@code arr}, or -1 if the index
     * is out of bounds or the array reference is null.
     *
     * @param arr   the integer array
     * @param size  the logical size to treat as the array's valid range
     * @param index the requested index
     * @return      the element value, or -1 on any validation failure
     */
    public static int getValueFromArray(int[] arr, int size, int index) {
        if (arr == null || size <= 0 || size > arr.length) {
            System.err.println("Error: invalid array or size.");
            return -1;
        }

        if (index < 0 || index >= size) {
            System.err.println("Error: index " + index
                    + " is out of bounds (valid range: 0–" + (size - 1) + ").");
            return -1;
        }

        return arr[index];
    }

    public static void main(String[] args) {
        final int[] idSequence = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
        final int size = idSequence.length;

        System.out.println("idSequence has " + size + " elements (indices 0–" + (size - 1) + ").");
        System.out.print("Enter an index: ");
        System.out.flush();

        Scanner scanner = new Scanner(System.in);

        if (!scanner.hasNextLine()) {
            System.err.println("Error: no input received.");
            scanner.close();
            System.exit(-1);
        }

        String input = scanner.nextLine().trim();
        scanner.close();

        int index;
        try {
            /* Integer.parseInt rejects non-numeric text, floats, and int overflow */
            index = Integer.parseInt(input);
        } catch (NumberFormatException e) {
            System.err.println("Error: \"" + input + "\" is not a valid integer.");
            System.exit(-1);
            return; // unreachable; keeps compiler happy
        }

        int result = getValueFromArray(idSequence, size, index);
        System.out.println("Result: " + result);
        System.exit(result);
    }
}
