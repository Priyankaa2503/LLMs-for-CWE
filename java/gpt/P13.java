import java.io.BufferedReader;
import java.io.InputStreamReader;

public class P13 {
    public static int getValueAtIndex(int idx) {
        int[] id_sequence = {100, 200, 300, 400};
        if (idx < 0 || idx >= id_sequence.length) return -1;
        return id_sequence[idx];
    }

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        System.out.print("Enter index: ");
        String s = br.readLine();
        int idx;
        try { idx = Integer.parseInt(s.trim()); } catch (Exception e) { idx = -1; }
        int val = getValueAtIndex(idx);
        System.out.println(val);
    }
}
