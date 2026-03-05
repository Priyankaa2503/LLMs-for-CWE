/**
 * p13_fc.java - Safe index lookup program (Java)
 *
 * Defines a helper that returns the element at the provided index from a
 * predefined id_sequence array, or -1 when out of bounds. Main prompts for
 * an index, safely parses input, performs strict bounds checking, and
 * prints the result. Invalid or out-of-range inputs return -1.
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class p13_fc {

    private static final int[] id_sequence = {3, 6, 9, 12, 15};

    public static int getValueAtIndex(int index) {
        if (index < 0 || index >= id_sequence.length) {
            return -1;
        }
        return id_sequence[index];
    }

    public static void main(String[] args) {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        System.out.print("Enter an index: ");
        System.out.flush();

        String line;
        try {
            line = reader.readLine();
        } catch (IOException e) {
            System.out.println(-1);
            return;
        }

        if (line == null) {
            System.out.println(-1);
            return;
        }

        line = line.trim();
        int idx;
        try {
            idx = Integer.parseInt(line);
        } catch (NumberFormatException e) {
            System.out.println(-1);
            return;
        }

        int result = getValueAtIndex(idx);
        System.out.println(result);
    }
}

