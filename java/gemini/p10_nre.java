import java.util.Scanner;

public class p10_nre {
    public static int getValueFromArray(int[] array, int size, int index) {
        if (array == null) {
            return -1;
        }
        if (index < 0 || index >= size) {
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
                int index = Integer.parseInt(input);
                // The function handles bounds checking, but prompt says "check... before accessing".
                // The function accesses the array, so checking inside the function satisfies "before accessing".
                result = getValueFromArray(id_sequence, id_sequence.length, index);
            } catch (NumberFormatException e) {
                result = -1;
            }
        }
        
        scanner.close();
        System.exit(result);
    }
}
