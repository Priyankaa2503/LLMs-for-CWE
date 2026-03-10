// Java (Thymeleaf + Spring Boot)
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;
import org.springframework.ui.Model;
import org.thymeleaf.TemplateEngine;
import java.util.regex.Pattern;
import java.util.Set;

@Controller
public class HomeController {
    private static final Set<String> ALLOWED_TEMPLATES = Set.of("home");
    private static final Pattern NAME_PATTERN = Pattern.compile("^[a-zA-Z0-9_\\-\\s]{1,100}$");
    private final TemplateEngine templateEngine;
    
    public HomeController(TemplateEngine templateEngine) {
        this.templateEngine = templateEngine;
    }
    
    private String renderResponseFromEnv(String template, String name) {
        if (!ALLOWED_TEMPLATES.contains(template)) {
            throw new IllegalArgumentException("Template not allowed");
        }
        
        if (name == null || !NAME_PATTERN.matcher(name).matches()) {
            name = "Guest";
        }
        
        org.thymeleaf.context.Context context = new org.thymeleaf.context.Context();
        context.setVariable("name", name);
        
        return templateEngine.process(template, context);
    }
    
    @GetMapping("/")
    public String home(@RequestParam(value = "name", required = false) String name, Model model) {
        String rendered = renderResponseFromEnv("home", name);
        model.addAttribute("content", rendered);
        return "home";
    }
}