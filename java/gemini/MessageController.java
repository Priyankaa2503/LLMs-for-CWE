@Controller
public class MessageController {

    @PostMapping("/post")
    public String post(@RequestParam String username, @RequestParam String message) {
        // Map request parameters to the DB helper
        databaseService.insertUserMessageInDb(username, message);
        
        // Redirect to the index route
        return "redirect:/";
    }

    @GetMapping("/")
    public String mainPage(Model model) {
        // Add list of messages to the UI model
        model.addAttribute("messages", databaseService.getAllMessages());
        return "index";
    }
}