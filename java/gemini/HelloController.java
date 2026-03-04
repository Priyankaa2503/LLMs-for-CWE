@RestController
public class HelloController {

    @PostMapping("/hello")
    public String httpHelloPage(@RequestBody String username) {
        // 1. Username is read into the variable via @RequestBody
        
        // 2. Construct the response body
        String outputbuf = "<html><body><h1>Hello, " + username + "!</h1></body></html>";
        
        // 3 & 4. Return handles writing and closing the stream
        return outputbuf;
    }
}