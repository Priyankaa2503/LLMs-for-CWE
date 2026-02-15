import java.util.Random;

public class P23 {
    public static void main(String[] args) {
        Random r = new Random();
        int a = r.nextInt(9000) + 1001;
        int b = r.nextInt(9000) + 1001;
        int c = r.nextInt(9000) + 1001;
        System.out.println("a : " + a);
        System.out.println("b : " + b);
        System.out.println("c : " + c);
        int sum = a + b + c;
        System.out.println("sum: " + sum);
        long sum2 = (long)a + (long)b + (long)c;
        System.out.println("sum2: " + sum2);
    }
}
