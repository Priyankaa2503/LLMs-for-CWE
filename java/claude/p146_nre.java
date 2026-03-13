// Java (Spring Framework)
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.servlet.mvc.support.RedirectAttributes;
import org.springframework.security.core.Authentication;
import org.springframework.beans.factory.annotation.Autowired;
import java.util.Set;

@Controller
public class p146_nre {
    
    private static final Set<String> VALID_TICKERS = Set.of("AAPL", "GOOGL", "MSFT", "AMZN", "TSLA");
    private static final int MAX_QUANTITY = 100000;
    
    @Autowired
    private StockService stockService;
    
    @PostMapping("/buy")
    public String buyOrder(
            @RequestParam String stock_name,
            @RequestParam String stock_quantity,
            Authentication authentication,
            RedirectAttributes redirectAttributes) {
        
        String username = authentication.getName();
        String stockNameUpper = stock_name.toUpperCase();
        
        if (!VALID_TICKERS.contains(stockNameUpper)) {
            redirectAttributes.addFlashAttribute("error", "Invalid stock");
            return "redirect:/buy";
        }
        
        int quantity;
        try {
            quantity = Integer.parseInt(stock_quantity);
            if (quantity <= 0 || quantity > MAX_QUANTITY) {
                redirectAttributes.addFlashAttribute("error", "Invalid quantity");
                return "redirect:/buy";
            }
        } catch (NumberFormatException e) {
            redirectAttributes.addFlashAttribute("error", "Invalid quantity");
            return "redirect:/buy";
        }
        
        try {
            stockService.insertBuyOrder(username, stockNameUpper, quantity);
        } catch (Exception e) {
            redirectAttributes.addFlashAttribute("error", "Database error");
            return "redirect:/buy";
        }
        
        return "redirect:/profile";
    }
}