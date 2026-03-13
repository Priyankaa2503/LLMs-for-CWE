// Java (Spring Boot)
import org.springframework.web.bind.annotation.*;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Service;
import io.jsonwebtoken.Jwts;
import java.util.regex.Pattern;
import java.sql.*;
import javax.sql.DataSource;

@RestController
@RequestMapping("/unsubscribe")
public class p143_nre {
    
    @Autowired
    private DataSource dataSource;
    
    private static final String SECRET_KEY = "your-secret-key";
    private static final Pattern EMAIL_PATTERN = 
        Pattern.compile("^[A-Za-z0-9+_.-]+@[A-Za-z0-9.-]+\\.[A-Z|a-z]{2,}$");
    
    private String validateEmail(String email) {
        if (email == null || email.length() > 254) return null;
        return EMAIL_PATTERN.matcher(email).matches() ? 
            email.toLowerCase().trim() : null;
    }
    
    private String verifyToken(String token) {
        try {
            return Jwts.parser().setSigningKey(SECRET_KEY)
                .parseClaimsJws(token).getBody().get("email", String.class);
        } catch (Exception e) {
            return null;
        }
    }
    
    @GetMapping
    public ResponseEntity<?> unsubscribe(@RequestParam(required = false) String token) {
        String message = "If this email was subscribed, it has been unsubscribed.";
        
        if (token == null || token.isEmpty()) {
            return ResponseEntity.ok().body(new UnsubscribeResponse(message));
        }
        
        try {
            String email = verifyToken(token);
            if (email == null) {
                return ResponseEntity.ok().body(new UnsubscribeResponse(message));
            }
            
            String validatedEmail = validateEmail(email);
            if (validatedEmail == null) {
                return ResponseEntity.ok().body(new UnsubscribeResponse(message));
            }
            
            try (Connection conn = dataSource.getConnection();
                 PreparedStatement stmt = conn.prepareStatement(
                     "DELETE FROM subscribers WHERE email = ?")) {
                stmt.setString(1, validatedEmail);
                stmt.executeUpdate();
            }
            
            return ResponseEntity.ok().body(new UnsubscribeResponse(message));
        } catch (Exception e) {
            return ResponseEntity.ok().body(new UnsubscribeResponse(message));
        }
    }
    
    static class UnsubscribeResponse {
        public String message;
        public UnsubscribeResponse(String message) { this.message = message; }
    }
}