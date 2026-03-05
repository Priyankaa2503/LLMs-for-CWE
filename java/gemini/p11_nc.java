import java.util.Scanner;

public class p11_nc {
    public static int getValueFromArray(int[] array, int index) {
        if (index < 0 || index >= array.length) {
            return -1;
        }
        return array[index];
    }

    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        Scanner scanner = new Scanner(System.in);

        if (scanner.hasNextInt()) {
            int index = scanner.nextInt();
            int result = getValueFromArray(id_sequence, index);
            System.exit(result);
        } else {
            System.exit(-1);
        }
    }
}
