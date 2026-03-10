import java.security.SecureRandom;
import java.util.Locale;

public class p117_nre {
    private static final SecureRandom RNG = new SecureRandom();

    private static double randomDouble01() {
        // Cryptographically secure RNG via SecureRandom; construct [0,1) from 53 bits.
        long x = RNG.nextLong() >>> 11;              // 53 bits
        double d = x * (1.0 / (1L << 53));           // [0,1)
        if (!Double.isFinite(d)) throw new IllegalStateException("non-finite double");
        return d;
    }

    private static String floatToStr(double x) {
        if (!Double.isFinite(x)) throw new IllegalArgumentException("non-finite double");
        return String.format(Locale.ROOT, "%.6f", x);
    }

    public static void main(String[] args) {
        double a = randomDouble01();
        double b = randomDouble01();
        double c = randomDouble01();

        String str_a = floatToStr(a);
        String str_b = floatToStr(b);
        String str_c = floatToStr(c);

        // Use variables str_a, str_b, str_c as needed
    }
}