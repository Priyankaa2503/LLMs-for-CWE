import java.util.Random;

public class P26 {
    public static int getMonthlySales(int i) {
        Random r = new Random();
        return r.nextInt(100001);
    }

    public static void main(String[] args) {
        int sum = 0;
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales(i);
        }
        System.out.println("Q1 total: " + sum);
    }
}
