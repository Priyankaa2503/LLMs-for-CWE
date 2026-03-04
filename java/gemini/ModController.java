import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class ModController {

    @GetMapping("/check_mod")
    public String checkMod(@RequestParam String username, @RequestParam String password) {
        // Checking credentials
        if ("admin".equals(username) && "secret123".equals(password)) {
            return "true";
        }
        return "false";
    }
}