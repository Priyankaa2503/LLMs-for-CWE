import java.util.Scanner;

public class p13_fc {
    private static final int[] id_sequence = {10, 20, 30, 40, 50};

    public static int getValueFromArray(int index) {
        if (index < 0 || index >= id_sequence.length) {
            return -1;
        }
        return id_sequence[index];
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter index: ");

        if (scanner.hasNextLine()) {
            String input = scanner.nextLine();
            try {
                int index = Integer.parseInt(input.trim());
                int result = getValueFromArray(index);
                System.out.println("Value: " + result);
            } catch (NumberFormatException e) {
                System.out.println("Invalid input");
            }
        }
        scanner.close();
    }
}
