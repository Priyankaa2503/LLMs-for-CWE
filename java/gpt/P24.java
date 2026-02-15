import java.util.Random;

public class P24 {
    public static void main(String[] args) {
        Random r = new Random();
        int a = r.nextInt(991) + 10; // 10..1000
        int b = r.nextInt(991) + 10;
        int diff = a - b;
        System.out.println("a: " + a);
        System.out.println("b: " + b);
        System.out.println("difference: " + diff);
    }
}
