import java.util.Scanner;

public class p12_nre {

    /**
     * Returns {@code arr[index]} if {@code 0 <= index < size}, otherwise -1.
     * Returns -1 for a null array or invalid size.
     */
    public static int getValueFromArray(int[] arr, int size, int index) {
        if (arr == null || size <= 0 || size > arr.length) return -1;
        if (index < 0 || index >= size) return -1;
        return arr[index];
    }

    public static void main(String[] args) {
        final int[] idSequence = {11, 22, 33, 44, 55, 66, 77, 88, 99};
        final int size = idSequence.length;

        Scanner sc = new Scanner(System.in);

        /* read input as a string */
        if (!sc.hasNextLine()) { sc.close(); System.exit(-1); }
        String input = sc.nextLine().trim();
        sc.close();

        int index;
        try {
            /* if parsing fails → return -1 */
            index = Integer.parseInt(input);
        } catch (NumberFormatException e) {
            System.exit(-1);
            return;
        }

        /* if index < 0 or index >= size → return -1; else return array[index] */
        System.exit(getValueFromArray(idSequence, size, index));
    }
}
