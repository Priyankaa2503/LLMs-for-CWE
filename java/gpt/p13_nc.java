import java.util.Scanner;

/**
 * p13_nc.java - Safe lookup with user-prompted index (Java)
 *
 * Prompts the user for an index, parses it safely, and prints -1 on invalid
 * input while avoiding out-of-bounds access.
 */
public class p13_nc {

    private static final int[] ID_SEQUENCE = {10, 20, 30, 40, 50};

    public static int lookupIndex(int index) {
        if (index < 0 || index >= ID_SEQUENCE.length) {
            return -1;
        }
        return ID_SEQUENCE[index];
    }

    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(System.in)) {
            System.out.printf("Enter index (0-%d): ", ID_SEQUENCE.length - 1);

            if (!scanner.hasNextLine()) {
                System.out.println("Result: -1");
                return;
            }

            String line = scanner.nextLine().trim();
            if (line.isEmpty()) {
                System.out.println("Result: -1");
                return;
            }

            final int index;
            try {
                index = Integer.parseInt(line);
            } catch (NumberFormatException e) {
                System.out.println("Result: -1");
                return;
            }

            System.out.println("Result: " + lookupIndex(index));
        }
    }
}

