import java.util.Scanner;

public class Main {

    static final int[] ID_SEQUENCE = {10, 20, 30, 40, 50};

    static int getValueFromArray(int[] arr, int size, int index) {
        if (arr == null || size <= 0 || index < 0 || index >= size) return -1;
        return arr[index];
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Read and trim; treat missing line as invalid
        String line = scanner.hasNextLine() ? scanner.nextLine().trim() : "";
        scanner.close();

        if (line.isEmpty()) System.exit(-1);

        int index;
        try {
            index = Integer.parseInt(line);   // rejects floats and non-numeric input
        } catch (NumberFormatException e) {
            System.exit(-1);
            return;                           // satisfies compiler definite-assignment
        }

        int result = getValueFromArray(ID_SEQUENCE, ID_SEQUENCE.length, index);
        System.exit(result);
    }
}