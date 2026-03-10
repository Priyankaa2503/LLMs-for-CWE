// Java
import java.security.SecureRandom;

public class SecureFloatStringConversion {
    public static void main(String[] args) {
        SecureRandom secureRandom = new SecureRandom();
        
        // Generate three cryptographically secure random doubles
        double rand_a = secureRandom.nextDouble();
        double rand_b = secureRandom.nextDouble();
        double rand_c = secureRandom.nextDouble();
        
        // Convert to strings using safe method
        String str_a = safeDoubleToString(rand_a);
        String str_b = safeDoubleToString(rand_b);
        String str_c = safeDoubleToString(rand_c);
    }
    
    private static String safeDoubleToString(double value) {
        if (!Double.isFinite(value)) {
            throw new IllegalArgumentException("Double is not finite: " + value);
        }
        return Double.toString(value);
    }
}