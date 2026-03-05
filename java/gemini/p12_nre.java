import java.util.Scanner;

public class p12_nre {
    public static int getValueFromArray(int[] array, int size, int index) {
        // if index < 0 or index >= size return -1
        if (array == null || index < 0 || index >= size) {
            return -1;
        }
        // else return array[index]
        return array[index];
    }

    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        Scanner scanner = new Scanner(System.in);
        int result = -1;

        if (scanner.hasNext()) {
            String input = scanner.next();
            try {
                // read input as a string -> try to parse an integer safely
                int index = Integer.parseInt(input);
                // Call function
                result = getValueFromArray(id_sequence, id_sequence.length, index);
            } catch (NumberFormatException e) {
                // if parsing fails return -1
                result = -1;
            }
        }
        
        scanner.close();
        System.exit(result);
    }
}
