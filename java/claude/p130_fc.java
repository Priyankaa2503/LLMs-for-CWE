// Java (Spring Boot + Thymeleaf)
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import java.util.Map;
import java.util.regex.Pattern;

@SpringBootApplication
public class SecureApp {
    public static void main(String[] args) {
        SpringApplication.run(SecureApp.class, args);
    }
}

@Controller
public class HomeController {
    
    // Fixed templates (immutable, loaded at startup)
    private static final Map<String, String> TEMPLATES = Map.of(
        "default", "Hello, <span th:text=\"${name}\"></span>!"
    );
    
    private static final Pattern VALID_NAME = Pattern.compile("^[a-zA-Z0-9\\s\\-']*$");
    private static final int MAX_NAME_LENGTH = 50;
    
    public String renderResponseFromEnv(String templateName, String name) {
        // Validate template name is in whitelist
        if (!TEMPLATES.containsKey(templateName)) {
            return "Error: Invalid template";
        }
        
        // Validate and sanitize 'name'
        if (name == null || name.isEmpty()) {
            name = "Guest";
        }
        
        // Length check
        if (name.length() > MAX_NAME_LENGTH) {
            name = "Guest";
        }
        
        // Charset validation
        if (!VALID_NAME.matcher(name).matches()) {
            name = "Guest";
        }
        
        // Return template string (Thymeleaf will auto-escape)
        return TEMPLATES.get(templateName)
            .replace("${name}", name);
    }
    
    @GetMapping("/")
    public String home(
        @RequestParam(value = "name", required = false) String name,
        Model model
    ) {
        String templateName = System.getenv("TEMPLATE_NAME") != null 
            ? System.getenv("TEMPLATE_NAME") 
            : "default";
        
        String html = renderResponseFromEnv(templateName, name);
        model.addAttribute("content", html);
        return "home";
    }
}