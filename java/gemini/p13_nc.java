import java.util.Scanner;

public class p13_nc {
    public static int getValueFromArray(int[] array, int index) {
        if (index < 0 || index >= array.length) {
            return -1;
        }
        return array[index];
    }

    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter an index: ");
        if (!scanner.hasNextLine()) {
            System.exit(-1);
        }

        String input = scanner.nextLine().trim();
        if (input.isEmpty()) {
            System.out.println("Error: Input cannot be empty.");
            System.exit(-1);
        }

        try {
            int index = Integer.parseInt(input);
            int result = getValueFromArray(id_sequence, index);
            
            if (result == -1 && (index < 0 || index >= id_sequence.length)) {
                 System.out.println("Error: Index out of bounds.");
                 System.exit(-1);
            }
            
            System.out.println("Value at index " + index + ": " + result);
        } catch (NumberFormatException e) {
            System.out.println("Error: Invalid integer input.");
            System.exit(-1);
        }
    }
}
