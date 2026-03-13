// Java (Spring Boot)
import org.springframework.web.bind.annotation.*;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Component;
import javax.crypto.Mac;
import javax.crypto.spec.SecretKeySpec;
import java.time.LocalDateTime;
import java.util.HashMap;
import java.util.Map;
import java.util.regex.Pattern;
import java.util.Base64;

@RestController
@RequestMapping("/api")
@Component
public class p143_nc {
    
    @Value("${app.secret-key}")
    private String secretKey;
    
    private final JdbcTemplate jdbcTemplate;
    private static final Pattern EMAIL_PATTERN = 
        Pattern.compile("^[A-Za-z0-9+_.-]+@(.+)$");
    
    public UnsubscribeController(JdbcTemplate jdbcTemplate) {
        this.jdbcTemplate = jdbcTemplate;
    }
    
    private String validateAndNormalizeEmail(String email) {
        if (email == null) return null;
        String trimmed = email.trim();
        if (!EMAIL_PATTERN.matcher(trimmed).matches()) {
            return null;
        }
        return trimmed.toLowerCase();
    }
    
    private String generateUnsubscribeToken(String email) {
        try {
            Mac mac = Mac.getInstance("HmacSHA256");
            SecretKeySpec secretKeySpec = new SecretKeySpec(
                secretKey.getBytes(), 0, secretKey.getBytes().length, "HmacSHA256"
            );
            mac.init(secretKeySpec);
            byte[] hash = mac.doFinal(email.toLowerCase().getBytes());
            return Base64.getEncoder().encodeToString(hash);
        } catch (Exception e) {
            return "";
        }
    }
    
    private boolean verifyUnsubscribeToken(String email, String token) {
        String expectedToken = generateUnsubscribeToken(email);
        return constantTimeEquals(token, expectedToken);
    }
    
    private boolean constantTimeEquals(String a, String b) {
        byte[] aBytes = a.getBytes();
        byte[] bBytes = b.getBytes();
        int result = aBytes.length ^ bBytes.length;
        for (int i = 0; i < Math.min(aBytes.length, bBytes.length); i++) {
            result |= aBytes[i] ^ bBytes[i];
        }
        return result == 0;
    }
    
    @GetMapping("/unsubscribe")
    public ResponseEntity<Map<String, String>> unsubscribe(
            @RequestParam(value = "email", required = false) String email,
            @RequestParam(value = "token", required = false) String token) {
        
        String normalizedEmail = validateAndNormalizeEmail(email);
        if (normalizedEmail == null) {
            return ResponseEntity.ok(Map.of("message", "Unsubscribe request processed."));
        }
        
        if (token == null || !verifyUnsubscribeToken(normalizedEmail, token)) {
            return ResponseEntity.ok(Map.of("message", "Unsubscribe request processed."));
        }
        
        try {
            Integer userId = jdbcTemplate.queryForObject(
                "SELECT id FROM users WHERE email = ?",
                new Object[]{normalizedEmail},
                Integer.class
            );
            
            if (userId != null) {
                jdbcTemplate.update("DELETE FROM users WHERE email = ?", normalizedEmail);
                jdbcTemplate.update(
                    "INSERT INTO unsubscribe_log (email, timestamp) VALUES (?, ?)",
                    normalizedEmail, LocalDateTime.now()
                );
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        
        return ResponseEntity.ok(Map.of("message", "Unsubscribe request processed."));
    }
}