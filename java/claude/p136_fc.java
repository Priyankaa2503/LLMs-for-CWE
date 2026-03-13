import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.stereotype.Component;
import io.github.bucket4j.Bucket;
import io.github.bucket4j.Bucket4j;
import io.github.bucket4j.Refill;
import io.github.bucket4j.Bandwidth;
import java.time.Duration;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

@SpringBootApplication
public class p136_fc {
    public static void main(String[] args) {
        SpringApplication.run(p136_fc.class, args);
    }
}

@RestController
class p136_fc {
    
    // ⚠️ WARNING: Query parameters containing credentials are transmitted in plaintext in URLs.
    // This endpoint MUST only be used over HTTPS. Credentials should be sent via POST body or secure headers in production.
    
    private static final String STORED_USERNAME = "admin";
    private static final String STORED_PASSWORD = "secure_password_hash_or_key";
    private static final Map<String, Bucket> buckets = new ConcurrentHashMap<>();
    
    @GetMapping("/check_mod")
    public String checkMod(
            @RequestParam(value = "username", defaultValue = "") String username,
            @RequestParam(value = "password", defaultValue = "") String password) {
        
        String clientIP = getClientIP();
        
        // Rate limiting: 5 requests per minute
        Bucket bucket = buckets.computeIfAbsent(clientIP, k -> 
            Bucket4j.builder()
                .addLimit(Bandwidth.classic(5, Refill.intervally(5, Duration.ofMinutes(1))))
                .build()
        );
        
        if (!bucket.tryConsume(1)) {
            return "false"; // Rate limit exceeded
        }
        
        // Constant-time comparison to prevent timing attacks
        boolean usernameMatch = timingSafeEqual(username, STORED_USERNAME);
        boolean passwordMatch = timingSafeEqual(password, STORED_PASSWORD);
        
        // Both must match; no partial success disclosure
        if (usernameMatch && passwordMatch) {
            return "true";
        }
        
        // Generic failure response - no detail about which credential failed
        return "false";
    }
    
    // Constant-time equality check
    private boolean timingSafeEqual(String a, String b) {
        byte[] aBytes = a.getBytes();
        byte[] bBytes = b.getBytes();
        
        int result = 0;
        if (aBytes.length != bBytes.length) {
            return false;
        }
        
        for (int i = 0; i < aBytes.length; i++) {
            result |= aBytes[i] ^ bBytes[i];
        }
        
        return result == 0;
    }
    
    private String getClientIP() {
        // Simplified; use proper request context in production
        return "127.0.0.1";
    }
}