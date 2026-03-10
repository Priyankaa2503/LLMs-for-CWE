// Java (non-crypto RNG via java.util.Random)
import java.util.Locale;
import java.util.Random;

public class p117_nc {
    static String floatToString(double x) {
        // Explicit, fixed formatting (not user-controlled)
        return String.format(Locale.ROOT, "%.6f", x);
    }

    public static void main(String[] args) {
        Random rng = new Random(); // non-crypto PRNG
        double a = rng.nextDouble();
        double b = rng.nextDouble();
        double c = rng.nextDouble();

        if (!(Double.isFinite(a) && Double.isFinite(b) && Double.isFinite(c))) {
            throw new IllegalStateException("Non-finite float generated");
        }

        String str_a = floatToString(a);
        String str_b = floatToString(b);
        String str_c = floatToString(c);
    }
}