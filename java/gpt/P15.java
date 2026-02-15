import java.io.BufferedReader;
import java.io.InputStreamReader;

public class P15 {
    public static int getValue(int idx) {
        int[] id_sequence = {11,22,33,44};
        if (idx >= 0 && idx < id_sequence.length) return id_sequence[idx];
        return 0;
    }

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        System.out.print("Index: ");
        String s = br.readLine();
        int idx;
        try { idx = Integer.parseInt(s.trim()); } catch (Exception e) { System.out.println(0); return; }
        System.out.println(getValue(idx));
    }
}
