import java.util.Scanner;

public class Solution {

    static int getValueFromArray(int[] arr, int size, int index) {
        if (arr == null || size <= 0 || index < 0 || index >= size)
            return -1;
        return arr[index];
    }

    public static void main(String[] args) {
        int[] arr = {10, 20, 30, 40, 50};
        int size = arr.length;

        int index;
        try (Scanner scanner = new Scanner(System.in)) {
            String line = scanner.nextLine().trim();
            index = Integer.parseInt(line);
        } catch (Exception e) {
            // NumberFormatException, NoSuchElementException, or IOException
            System.exit(255);
            return; // satisfies compiler; never reached
        }

        int result = getValueFromArray(arr, size, index);
        System.exit(result == -1 ? 255 : result);
    }
}