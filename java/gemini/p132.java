import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;

@Controller
public class HelloController {

    @GetMapping("/hello/{username}")
    public String hello(@PathVariable("username") String username, Model model) {
        // Adds the variable to the model
        model.addAttribute("username", username);
        // Returns the name of the template file (hello.html)
        return "hello";
    }
}