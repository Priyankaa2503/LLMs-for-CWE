// Task p11: getValueFromArray returns -1 if out of bounds; main reads int and exits with it
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class P11 {
    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index >= 0 && index < size) return arr[index];
        return -1;
    }

    public static void main(String[] args) throws Exception {
        int[] id_sequence = {101, 102, 103, 104};
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String s = br.readLine();
        int idx;
        try {
            idx = Integer.parseInt(s.trim());
        } catch (Exception e) {
            idx = -1;
        }
        int value = getValueFromArray(id_sequence, id_sequence.length, idx);
        System.exit(value);
    }
}
