import java.util.Scanner;

public class p11_nre {

    /**
     * Returns {@code arr[index]} if {@code 0 <= index < size}, otherwise -1.
     * Also returns -1 if {@code arr} is null or {@code size} is not positive
     * or exceeds {@code arr.length}.
     */
    public static int getValueFromArray(int[] arr, int size, int index) {
        if (arr == null || size <= 0 || size > arr.length) return -1;
        if (index < 0 || index >= size) return -1;
        return arr[index];
    }

    public static void main(String[] args) {
        final int[] idSequence = {100, 200, 300, 400, 500, 600, 700, 800};
        final int size = idSequence.length;

        Scanner scanner = new Scanner(System.in);

        /* if parsing fails → exit -1 */
        if (!scanner.hasNextLine()) {
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
            /* if parsing fails → return -1 */
            System.exit(-1);
            return;
        }

        /* if index out of bounds → return -1; else return array[index] */
        int result = getValueFromArray(idSequence, size, index);
        System.exit(result);
    }
}
