import java.util.Scanner;

public class p11_fc {

    private static final int[] ID_SEQUENCE = {100, 200, 300, 400, 500};

    /**
     * Returns {@code array[index]} when {@code 0 <= index < size},
     * or -1 if the bounds check fails.
     *
     * @param array the source array
     * @param size  declared size to validate against
     * @param index requested index
     * @return      value at index, or -1 on invalid access
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
