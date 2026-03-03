import java.util.Scanner;

public class Main {
    static final int[] id_sequence = {10, 20, 30, 40, 50};

    static int getValue(int index) {
        if (index < 0 || index >= id_sequence.length) return -1;
        return id_sequence[index];
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index: ");

        if (!scanner.hasNextLine()) {
            System.out.println("Input error. Result: -1");
            return;
        }

        String input = scanner.nextLine().trim();

        if (!input.matches("-?\\d+")) {
            System.out.println("Invalid input. Result: -1");
            return;
        }

        try {
            int index = Integer.parseInt(input);
            System.out.println("Result: " + getValue(index));
        } catch (NumberFormatException e) {
            // Catches overflow beyond Integer range
            System.out.println("Invalid input. Result: -1");
        }
    }
}