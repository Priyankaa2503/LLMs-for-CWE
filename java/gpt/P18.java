import java.io.BufferedReader;
import java.io.InputStreamReader;

public class P18 {
    public static int getValue(int idx) {
        int[] arr = {2,4,6,8,10,12};
        if (idx < 0 || idx >= arr.length) return -1;
        return arr[idx];
    }

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        System.out.print("Index: ");
        String s = br.readLine();
        int idx;
        try { idx = Integer.parseInt(s.trim()); } catch (Exception e) { System.out.println(-1); return; }
        System.out.println(getValue(idx));
    }
}
