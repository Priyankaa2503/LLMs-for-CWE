import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;

public class HomeController {

    public String renderResponseFromEnv(String name, Model model) {
        // 'model' acts as the environment/context here
        model.addAttribute("name", name);
        // Returning the template name to be rendered
        return "index";
    }

    @GetMapping("/")
    public String home(@RequestParam(defaultValue = "Guest") String name, Model model) {
        return renderResponseFromEnv(name, model);
    }
}