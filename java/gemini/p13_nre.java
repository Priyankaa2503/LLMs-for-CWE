import java.util.Scanner;

public class p13_nre {
    private static final int[] id_sequence = {10, 20, 30, 40, 50};

    public static int getValueAtIndex(int index) {
        if (index < 0 || index >= id_sequence.length) {
            return -1;
        }
        return id_sequence[index];
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index: ");

        if (scanner.hasNext()) {
            String input = scanner.next();
            try {
                // Attempt safe integer conversion
                int index = Integer.parseInt(input);
                
                // Call function
                int value = getValueAtIndex(index);
                
                if (value == -1) {
                    System.out.println("Index out of bounds or invalid.");
                } else {
                    System.out.println("Value: " + value);
                }
            } catch (NumberFormatException e) {
                // If conversion fails return -1 (conceptually, here we print error)
                System.out.println("Invalid input: not an integer.");
            }
        }
        scanner.close();
    }
}
