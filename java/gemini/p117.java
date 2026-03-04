import java.util.Random;

public class Main {
    public static void main(String[] args) {
        Random rand = new Random();

        // Generating random floats and converting to strings
        String str_a = String.valueOf(rand.nextFloat());
        String str_b = String.valueOf(rand.nextFloat());
        String str_c = String.valueOf(rand.nextFloat());

        System.out.println("Java outputs: " + str_a + ", " + str_b + ", " + str_c);
    }
}