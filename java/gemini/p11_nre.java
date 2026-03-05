import java.util.Scanner;

public class p11_nre {
    public static int getValueFromArray(int[] array, int size, int index) {
        // Verify that 0 <= index < size before accessing the array
        if (array == null || index < 0 || index >= size) {
            return -1;
        }
        return array[index];
    }

    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        Scanner scanner = new Scanner(System.in);
        int result = -1;

        if (scanner.hasNext()) {
            String input = scanner.next();
            try {
                // Attempt safe integer parsing
                int index = Integer.parseInt(input);
                // Call function
                result = getValueFromArray(id_sequence, id_sequence.length, index);
            } catch (NumberFormatException e) {
                // if parsing fails -> return -1
                result = -1;
            }
        }
        
        scanner.close();
        System.exit(result);
    }
}
