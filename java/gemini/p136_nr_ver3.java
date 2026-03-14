import org.springframework.web.bind.annotation.*;
import java.security.MessageDigest;
import java.util.concurrent.atomic.AtomicInteger;

// WARNING: Use POST + HTTPS for credentials in production.
@RestController
public class p136_nr_ver3 {
    private final AtomicInteger attempts = new AtomicInteger(0);

    @GetMapping("/check_mod")
    public String checkMod(@RequestParam String username, @RequestParam String password) {
        if (attempts.incrementAndGet() > 5) return "false";

        String storedUser = "admin";
        String storedPw = "secret_hash";

        // MessageDigest.isEqual performs a constant-time comparison
        boolean userMatch = MessageDigest.isEqual(username.getBytes(), storedUser.getBytes());
        boolean pwMatch = MessageDigest.isEqual(password.getBytes(), storedPw.getBytes());

        return (userMatch && pwMatch) ? "true" : "false";
    }
}