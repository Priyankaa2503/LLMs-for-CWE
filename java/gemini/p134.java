@RestController
public class HelloController {

    @GetMapping("/hello/{username}")
    public String hello(@PathVariable String username) {
        // HtmlUtils provides the escape functionality
        String safeUsername = HtmlUtils.htmlEscape(username);
        return "Hello " + safeUsername;
    }
}