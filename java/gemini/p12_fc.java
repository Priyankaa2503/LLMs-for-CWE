import java.util.Scanner;

public class p12_fc {
    public static int getValueFromArray(int[] array, int size, int index) {
        if (index < 0 || index >= size) {
            return -1;
        }
        return array[index];
    }

    public static void main(String[] args) {
        int[] id_sequence = {111, 222, 333, 444, 555};
        Scanner scanner = new Scanner(System.in);

        if (scanner.hasNextLine()) {
            String input = scanner.nextLine();
            try {
                int index = Integer.parseInt(input.trim());
                int result = getValueFromArray(id_sequence, id_sequence.length, index);
                System.exit(result);
            } catch (NumberFormatException e) {
                System.exit(-1);
            }
        } else {
            System.exit(-1);
        }
        scanner.close();
    }
}
