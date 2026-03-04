import org.springframework.boot.SpringApplication;
import org.springframework.web.bind.annotation.*;

@RestController                     // 1 & 2. Part of app setup
public class HelloController {

    @GetMapping("/")                // 3. Decorator (Annotation) for URL
    public String index() {         // 4. Function (Method)
        return "Hello, World!";     // 5. Return the message
    }

    public static void main(String[] args) {
        SpringApplication.run(HelloController.class, args); // 6. Run
    }
}