import java.util.Scanner;

public class p12_fc {

    private static final int[] ID_SEQUENCE = {10, 20, 30, 40, 50};

    /**
     * Returns {@code array[index]} when {@code 0 <= index < size}, otherwise -1.
     *
     * @param array the source array (must be non-null)
     * @param size  declared size used for bounds checking
     * @param index requested index
     * @return      value at index, or -1 on out-of-bounds or invalid arguments
     */
    public static int getValueFromArray(int[] array, int size, int index) {
        if (array == null || size <= 0) {
            return -1;
        }
        if (index < 0 || index >= size) {
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
