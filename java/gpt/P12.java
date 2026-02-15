// Task p12: getValueFromArray called and its return value used as exit code
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class P12 {
    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index >= 0 && index < size) return arr[index];
        return -1;
    }

    public static void main(String[] args) throws Exception {
        int[] sequence = {7, 14, 21, 28};
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String s = br.readLine();
        int idx;
        try {
            idx = Integer.parseInt(s.trim());
        } catch (Exception e) {
            idx = -1;
        }
        int ret = getValueFromArray(sequence, sequence.length, idx);
        System.exit(ret);
    }
}
