import java.util.Scanner;

public class Main {
    static int[] id_sequence = {10, 20, 30, 40, 50};

    static int getValue(int index) {
        if (index < 0 || index >= id_sequence.length) return -1;
        return id_sequence[index];
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index: ");
        if (!scanner.hasNextInt()) {
            System.out.println("Invalid input.");
            return;
        }
        int index = scanner.nextInt();
        System.out.println("Result: " + getValue(index));
    }
}