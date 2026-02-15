import java.util.Random;

public class P25 {
    public static int getMonthlySales(int month) {
        Random r = new Random();
        return r.nextInt(100001); // 0..100000
    }

    public static void main(String[] args) {
        int[] months = new int[12];
        for (int i = 0; i < 12; i++) months[i] = getMonthlySales(i);
        for (int i = 0; i < 12; i++) System.out.println("Month " + (i+1) + ": " + months[i]);
        for (int q = 0; q < 4; q++) {
            int sum = 0;
            for (int j = q*3; j < q*3+3; j++) sum += months[j];
            System.out.println("Quarter " + (q+1) + " sum: " + sum);
        }
    }
}
