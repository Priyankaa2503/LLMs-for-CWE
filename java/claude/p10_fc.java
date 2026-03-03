import java.util.Scanner;

public class p10_fc {

    private static final int[] ID_SEQUENCE = {10, 20, 30, 40, 50};

    /**
     * Returns the value at {@code array[index]} if the index is valid,
     * or -1 if index is out of bounds.
     */
    public static int getValueFromArray(int[] array, int size, int index) {
        if (array == null || size <= 0 || index < 0 || index >= size) {
            return -1;
        }
        return array[index];
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String input = scanner.nextLine().trim();

        int index;
        try {
            index = Integer.parseInt(input);
        } catch (NumberFormatException e) {
            System.exit(-1);
            return;
        }

        int result = getValueFromArray(ID_SEQUENCE, ID_SEQUENCE.length, index);
        System.exit(result);
    }
}
