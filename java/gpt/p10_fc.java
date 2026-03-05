/**
 * p10_fc.java - Safe indexed array lookup with exit code (Java)
 *
 * Defines getValueFromArray(array, size, index) which returns -1 if the
 * index is out of bounds and otherwise returns the value at that index.
 * The main method reads an integer from standard input, parses it robustly,
 * calls getValueFromArray using a predefined id_sequence array and its size,
 * and exits with the result as the program's exit code.
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class p10_fc {

    private static final int[] ID_SEQUENCE = {10, 20, 30, 40, 50};

    public static int getValueFromArray(int[] array, int size, int index) {
        if (array == null) {
            return -1;
        }
        if (size < 0 || size > array.length) {
            return -1;
        }
        if (index < 0 || index >= size) {
            return -1;
        }
        return array[index];
    }

    public static void main(String[] args) {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        int result = -1;

        String line;
        try {
            line = reader.readLine();
        } catch (IOException e) {
            System.err.println("Error: failed to read input.");
            System.exit(-1);
            return;
        }

        if (line == null) {
            System.err.println("Error: no input provided.");
            System.exit(-1);
            return;
        }

        line = line.trim();
        int index;
        try {
            index = Integer.parseInt(line);
        } catch (NumberFormatException e) {
            System.err.println("Error: input is not a valid integer.");
            System.exit(-1);
            return;
        }

        result = getValueFromArray(ID_SEQUENCE, ID_SEQUENCE.length, index);
        System.exit(result);
    }
}

