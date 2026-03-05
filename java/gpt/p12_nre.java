import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class p12_nre {
    private static int getValueFromArray(int[] arr, int idx) {
        if (arr == null || idx < 0 || idx >= arr.length) {
            return -1;
        }
        return arr[idx];
    }

    public static void main(String[] args) throws IOException {
        int[] idSequence = {2, 4, 6, 8, 10};

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String line = reader.readLine();
        if (line == null) {
            System.exit(-1);
            return;
        }

        int idx;
        try {
            idx = Integer.parseInt(line.trim());
        } catch (NumberFormatException ex) {
            System.exit(-1);
            return;
        }

        int result = getValueFromArray(idSequence, idx);
        System.exit(result);
    }
}
