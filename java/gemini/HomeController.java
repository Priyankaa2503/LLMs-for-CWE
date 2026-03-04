@Controller
public class HomeController {

    public String renderResponseFromEnv(Model model, String name) {
        // 1. Name is passed from request mapping
        // 2 & 3. Add to model and return template name
        model.addAttribute("name", name);
        return "home_template"; 
    }

    @GetMapping("/")
    public String home(@RequestParam(defaultValue = "Guest") String name, Model model) {
        return renderResponseFromEnv(model, name);
    }
}