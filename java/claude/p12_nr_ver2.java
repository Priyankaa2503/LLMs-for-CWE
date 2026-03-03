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

        Scanner scanner = new Scanner(System.in);
        int index;

        try {
            String line = scanner.nextLine().trim();
            index = Integer.parseInt(line);
        } catch (Exception e) {
            System.exit(255);
            return;
        }

        int result = getValueFromArray(arr, size, index);
        System.exit(result == -1 ? 255 : result);
    }
}