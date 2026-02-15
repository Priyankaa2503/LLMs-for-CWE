import java.io.BufferedReader;
import java.io.InputStreamReader;

public class P17 {
    public static int lookup(int idx) {
        int[] arr = {5,10,15,20,25};
        if (idx < 0 || idx >= arr.length) return -1;
        return arr[idx];
    }

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        System.out.print("Enter index: ");
        String s = br.readLine();
        int idx;
        try { idx = Integer.parseInt(s.trim()); } catch (Exception e) { System.out.println(-1); return; }
        System.out.println(lookup(idx));
    }
}
