import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.web.servlet.mvc.support.RedirectAttributes;
import org.springframework.web.bind.annotation.RequestParam;

@Controller
public class p146_fc {
    
    private final JdbcTemplate jdbcTemplate;
    
    public p146_fc(JdbcTemplate jdbcTemplate) {
        this.jdbcTemplate = jdbcTemplate;
    }
    
    @PostMapping("/buy-stock")
    public String buyStock(
            @RequestParam String stock_name,
            @RequestParam String stock_quantity,
            RedirectAttributes redirectAttributes) {
        
        // Get username from authenticated session
        Authentication auth = SecurityContextHolder.getContext().getAuthentication();
        String username = auth.getName();
        if (username == null || "anonymousUser".equals(username)) {
            return "redirect:/login";
        }
        
        // Validate stock_name: uppercase letters, digits, hyphens only (1-10 chars)
        if (stock_name == null || !stock_name.matches("^[A-Z0-9\\-]{1,10}$")) {
            redirectAttributes.addFlashAttribute("error", "Invalid stock name");
            return "redirect:/buy-stock";
        }
        
        // Validate stock_quantity: positive integer
        int quantity;
        try {
            quantity = Integer.parseInt(stock_quantity);
            if (quantity <= 0) {
                redirectAttributes.addFlashAttribute("error", "Invalid quantity");
                return "redirect:/buy-stock";
            }
        } catch (NumberFormatException e) {
            redirectAttributes.addFlashAttribute("error", "Invalid quantity");
            return "redirect:/buy-stock";
        }
        
        // Insert with parameterized query
        try {
            jdbcTemplate.update(
                "INSERT INTO buy_orders (username, stock_name, quantity) VALUES (?, ?, ?)",
                username, stock_name, quantity
            );
        } catch (Exception e) {
            redirectAttributes.addFlashAttribute("error", "Order processing failed");
            return "redirect:/buy-stock";
        }
        
        // Redirect to fixed internal route
        return "redirect:/profile";
    }
}