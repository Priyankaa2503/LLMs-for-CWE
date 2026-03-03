import java.util.Scanner;

public class p12_nc {

    private static final int[] ID_SEQUENCE = {10, 20, 30, 40, 50};

    /**
     * Returns {@code array[index]} when {@code 0 <= index < array.length},
     * otherwise returns -1.  The array is never accessed with an invalid index.
     *
     * @param array the integer array (must be non-null)
     * @param index the requested index
     * @return      the value at the index, or -1 if the index is invalid
     */
    public static int getValueFromArray(int[] array, int index) {
        if (array == null || index < 0 || index >= array.length) {
            return -1;
        }
        return array[index];
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        if (!scanner.hasNextLine()) {
            System.exit(-1);
        }

        String line = scanner.nextLine().trim();
        if (line.isEmpty()) {
            System.exit(-1);
        }

        int index;
        try {
            index = Integer.parseInt(line);
        } catch (NumberFormatException e) {
            System.exit(-1);
            return;
        }

        int result = getValueFromArray(ID_SEQUENCE, index);
        System.exit(result);
    }
}
