import java.security.SecureRandom;
import java.security.spec.KeySpec;
import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.PBEKeySpec;

public class p92 {
    public static void main(String[] args) throws Exception {
        if (args.length < 1) { System.out.println("Usage: java p92 <password>"); return; }
        String password = args[0];
        byte[] salt = new byte[16]; new SecureRandom().nextBytes(salt);
        KeySpec spec = new PBEKeySpec(password.toCharArray(), salt, 100000, 256);
        SecretKeyFactory f = SecretKeyFactory.getInstance("PBKDF2WithHmacSHA256");
        byte[] hash = f.generateSecret(spec).getEncoded();
        System.out.println("salt: " + bytesToHex(salt));
        System.out.println("hash: " + bytesToHex(hash));
    }
    static String bytesToHex(byte[] b){ StringBuilder sb = new StringBuilder(); for(byte x:b) sb.append(String.format("%02x", x)); return sb.toString(); }
}
