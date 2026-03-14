import java.security.SecureRandom;
import java.util.Locale;

public class p117_nr_ver2 {
    private static final SecureRandom secureRandom = new SecureRandom();

    public static String floatToStr(double val) {
        if (!Double.isFinite(val)) {
            return "0.000000";
        }
        return String.format(Locale.US, "%.6f", val);
    }

    public static void main(String[] args) {
        String str_a = floatToStr(secureRandom.nextDouble() * 100.0);
        String str_b = floatToStr(secureRandom.nextDouble() * 100.0);
        String str_c = floatToStr(secureRandom.nextDouble() * 100.0);
    }
}