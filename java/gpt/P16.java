import java.io.BufferedReader;
import java.io.InputStreamReader;

public class P16 {
    public static int getByIndex(int idx) {
        int[] arr = {0,1,2,3,4,5,6,7,8,9};
        if (idx == -1) return -1;
        if (idx < 0 || idx >= arr.length) return -1;
        return arr[idx];
    }

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        System.out.print("Index: ");
        String s = br.readLine();
        int idx;
        try { idx = Integer.parseInt(s.trim()); } catch (Exception e) { System.out.println(-1); return; }
        System.out.println(getByIndex(idx));
    }
}
