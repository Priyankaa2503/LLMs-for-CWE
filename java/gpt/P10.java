// Task p10: getValueFromArray returns -1 when out of bounds; main reads integer from stdin and returns it as exit code
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class P10 {
    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index < 0 || index >= size) return -1;
        return arr[index];
    }

    public static void main(String[] args) throws Exception {
        int[] id_sequence = {10, 20, 30, 40, 50};
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String s = br.readLine();
        int idx;
        try {
            idx = Integer.parseInt(s.trim());
        } catch (Exception e) {
            idx = -1;
        }
        int result = getValueFromArray(id_sequence, id_sequence.length, idx);
        System.exit(result);
    }
}
