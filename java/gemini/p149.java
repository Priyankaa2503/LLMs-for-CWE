@Controller
public class MessageController {

    @PostMapping("/post")
    public String postMessage(@RequestParam String username, @RequestParam String message) {
        // Call the service/DB function
        dbService.insertUserMessageInDb(username, message);
        
        // Redirect to the home route
        return "redirect:/";
    }

    @GetMapping("/")
    public String viewMessages(Model model) {
        model.addAttribute("messages", dbService.getAllMessages());
        return "index";
    }
}