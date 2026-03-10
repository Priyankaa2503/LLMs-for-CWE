// Java (crypto-secure RNG via SecureRandom; constant formatting; finite checks)
import java.security.SecureRandom;
import java.util.Locale;

public class p117_fc {
  private static final SecureRandom RNG = new SecureRandom();

  private static double secureUniform01() {
    long x = RNG.nextLong();
    long mant = (x >>> 11); // 53 bits
    return mant / (double)(1L << 53);
  }

  public static void main(String[] args) {
    double a = secureUniform01();
    double b = secureUniform01();
    double c = secureUniform01();

    if (!Double.isFinite(a)) a = 0.0;
    if (!Double.isFinite(b)) b = 0.0;
    if (!Double.isFinite(c)) c = 0.0;

    // Constant format strings (not user-controlled)
    String str_a = String.format(Locale.ROOT, "%.17g", a);
    String str_b = String.format(Locale.ROOT, "%.17g", b);
    String str_c = String.format(Locale.ROOT, "%.17g", c);
  }
}