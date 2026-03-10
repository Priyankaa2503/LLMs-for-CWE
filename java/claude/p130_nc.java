import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.ui.Model;
import org.thymeleaf.TemplateEngine;

@Controller
public class HomeController {
    
    private final TemplateEngine templateEngine;
    
    public HomeController(TemplateEngine templateEngine) {
        this.templateEngine = templateEngine;
    }
    
    public String renderResponseFromEnv(
            TemplateEngine env,
            @RequestParam(value = "name", defaultValue = "Guest") String name,
            Model model) {
        
        // Validate name: allow alphanumeric and spaces only
        if (!name.matches("^[a-zA-Z0-9\\s]*$")) {
            name = "Guest";
        }
        
        // Add to model for template
        model.addAttribute("name", name);
        
        // Template is fixed and allowlisted
        // Thymeleaf has auto-escaping enabled by default
        return "greeting";
    }
    
    @GetMapping("/")
    public String home(
            TemplateEngine env,
            @RequestParam(value = "name", defaultValue = "Guest") String name,
            Model model) {
        
        // Call render function
        return renderResponseFromEnv(env, name, model);
    }
}