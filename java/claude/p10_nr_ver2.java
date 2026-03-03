import java.util.Scanner;

public class Main {
    static final int[] ID_SEQUENCE = {10, 20, 30, 40, 50};

    static int getValueFromArray(int[] arr, int size, int index) {
        if (arr == null || size <= 0 || index < 0 || index >= size) {
            return -1;
        }
        return arr[index];
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int index;

        try {
            String line = scanner.nextLine().trim();
            index = Integer.parseInt(line);
        } catch (NumberFormatException | java.util.NoSuchElementException e) {
            System.exit(-1);
            return;
        } finally {
            scanner.close();
        }

        int result = getValueFromArray(ID_SEQUENCE, ID_SEQUENCE.length, index);
        System.exit(result);
    }
}