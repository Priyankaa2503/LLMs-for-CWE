// Java (Spring Boot)
import org.springframework.web.bind.annotation.*;
import org.springframework.stereotype.Controller;
import java.util.*;
import java.util.concurrent.*;

@Controller
public class p136_nc {
    
    private final String CORRECT_USERNAME = "admin";
    private final String CORRECT_PASSWORD = "secret123";
    private final int MAX_ATTEMPTS = 5;
    private final long TIME_WINDOW = 60000; // milliseconds
    
    // Simple in-memory rate limiting (use Redis in production)
    private final Map<String, Queue<Long>> requestLog = new ConcurrentHashMap<>();
    
    @GetMapping("/check_mod")
    @ResponseBody
    public String checkMod(
            @RequestParam(required = false, defaultValue = "") String username,
            @RequestParam(required = false, defaultValue = "") String password,
            javax.servlet.http.HttpServletRequest servletRequest) {
        
        // SECURITY: In production, use POST+HTTPS instead of GET with credentials in URL
        String clientIp = servletRequest.getRemoteAddr();
        
        // Rate limiting check
        if (!checkRateLimit(clientIp)) {
            return "false";
        }
        
        // Constant-time comparison to prevent timing attacks
        boolean usernameMatch = constantTimeEquals(username, CORRECT_USERNAME);
        boolean passwordMatch = constantTimeEquals(password, CORRECT_PASSWORD);
        
        // Don't leak which field was wrong
        if (usernameMatch && passwordMatch) {
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
    
    private boolean checkRateLimit(String clientIp) {
        long now = System.currentTimeMillis();
        Queue<Long> times = requestLog.computeIfAbsent(clientIp, k -> new ConcurrentLinkedQueue<>());
        
        // Remove old entries
        times.removeIf(t -> now - t >= TIME_WINDOW);
        
        if (times.size() >= MAX_ATTEMPTS) {
            return false;
        }
        
        times.offer(now);
        return true;
    }
}