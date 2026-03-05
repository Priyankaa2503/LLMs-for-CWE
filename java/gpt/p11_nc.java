import java.util.Scanner;

/**
 * p11_nc.java - Safe indexed lookup with explicit parse handling (Java)
 *
 * Implements getValueFromArray(array, size, index) which returns the value at
 * array[index] when 0 <= index < size, and -1 otherwise. The main method reads
 * an integer index from standard input, validates that input is present and
 * parses cleanly, and exits with the function's result as the process exit code.
 */
public class p11_nc {

    private static final int[] ID_SEQUENCE = {10, 20, 30, 40, 50};

    /**
     * Returns the value at array[index] when the index is within bounds,
     * otherwise returns -1.
     */
    public static int getValueFromArray(int[] array, int size, int index) {
        if (array == null || size <= 0) {
            return -1;
        }
        if (index < 0 || index >= size) {
            return -1;
        }
        return array[index];
    }

    public static void main(String[] args) {
        int exitCode = -1;

        try (Scanner scanner = new Scanner(System.in)) {
            if (!scanner.hasNextLine()) {
                System.err.println("Error: no input available.");
                System.exit(-1);
            }

            String line = scanner.nextLine().trim();
            if (line.isEmpty()) {
                System.err.println("Error: input is empty.");
                System.exit(-1);
            }

            final int index;
            try {
                index = Integer.parseInt(line);
            } catch (NumberFormatException e) {
                System.err.printf("Error: \"%s\" is not a valid integer.%n", line);
                System.exit(-1);
                return;
            }

            exitCode = getValueFromArray(ID_SEQUENCE, ID_SEQUENCE.length, index);
        }

        System.exit(exitCode);
    }
}

