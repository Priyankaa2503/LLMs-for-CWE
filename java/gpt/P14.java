import java.io.BufferedReader;
import java.io.InputStreamReader;

public class P14 {
    public static int getValuePrompt() throws Exception {
        int[] id_sequence = {10, 20, 30, 40};
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        System.out.print("Enter index: ");
        String s = br.readLine();
        int idx;
        try { idx = Integer.parseInt(s.trim()); } catch (Exception e) { return -1; }
        if (idx < 0 || idx >= id_sequence.length) return -1;
        return id_sequence[idx];
    }

    public static void main(String[] args) throws Exception {
        int val = getValuePrompt();
        System.out.println(val);
        System.exit(0);
    }
}
