// Java (Spring Boot)
import org.springframework.web.bind.annotation.*;
import org.springframework.stereotype.Controller;
import java.util.*;
import java.security.MessageDigest;

@Controller
public class p136_nre {
    
    private static final Map<String, String> USERS = new HashMap<>();
    static {
        USERS.put("admin", "hashed_password_here"); // Use bcrypt in production
    }
    
    private static final Map<String, List<Long>> attempts = new HashMap<>();
    private static final int MAX_ATTEMPTS = 5;
    private static final long WINDOW = 300000; // 5 minutes
    
    @GetMapping("/check_mod")
    @ResponseBody
    public String checkMod(
            @RequestParam(value = "username", defaultValue = "") String username,
            @RequestParam(value = "password", defaultValue = "") String password,
            javax.servlet.http.HttpServletRequest request) {
        
        // NOTE: In production, use POST with HTTPS only
        // Do NOT pass credentials via URL parameters
        
        String clientIp = request.getRemoteAddr();
        long now = System.currentTimeMillis();
        
        // Rate limiting
        attempts.putIfAbsent(clientIp, new ArrayList<>());
        List<Long> clientAttempts = attempts.get(clientIp);
        clientAttempts.removeIf(t -> now - t >= WINDOW);
        
        if (clientAttempts.size() >= MAX_ATTEMPTS) {
            return "false";
        }
        clientAttempts.add(now);
        
        String storedHash = USERS.get(username);
        if (storedHash == null) {
            return "false";
        }
        
        // Constant-time comparison
        if (constantTimeEquals(password, storedHash)) {
            return "true";
        }
        
        return "false";
    }
    
    private boolean constantTimeEquals(String a, String b) {
        byte[] aBytes = a.getBytes();
        byte[] bBytes = b.getBytes();
        
        if (aBytes.length != bBytes.length) {
            return false;
        }
        
        int result = 0;
        for (int i = 0; i < aBytes.length; i++) {
            result |= aBytes[i] ^ bBytes[i];
        }
        
        return result == 0;
    }
}