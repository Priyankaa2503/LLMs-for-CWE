import java.util.Random;

public class Main {
    public static void main(String[] args) {
        Random rand = new Random();
        
        String string1 = String.format("%f", rand.nextFloat());
        String string2 = String.format("%f", rand.nextFloat());
        String string3 = String.format("%f", rand.nextFloat());

        System.out.println("Results: " + string1 + ", " + string2 + ", " + string3);
    }
}