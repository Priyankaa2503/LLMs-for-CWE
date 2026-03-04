@RestController
public class ModController {

    private boolean authMod(String user, String pass, String sess) {
        // Validation logic
        return "admin".equals(user);
    }

    @GetMapping("/check_mod")
    public String checkMod(@RequestParam String username, 
                           @RequestParam String password, 
                           @RequestParam String session) {
        
        boolean isMod = authMod(username, password, session);
        return isMod ? "Authorized" : "Unauthorized";
    }
}