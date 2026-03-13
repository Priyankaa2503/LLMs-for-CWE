// JAVA (Spring Boot)
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;
import javax.servlet.http.HttpSession;
import org.springframework.ui.Model;
import java.sql.*;
import javax.sql.DataSource;

@Controller
public class p146_nc {
    
    private static final Set<String> ALLOWED_STOCKS = 
        Set.of("AAPL", "GOOGL", "MSFT", "AMZN", "TSLA");
    private static final int MAX_QUANTITY = 10000;
    
    private final DataSource dataSource;
    
    @PostMapping("/buy-stock")
    public String buyStock(
        @RequestParam("stock_name") String stock_name,
        @RequestParam("stock_quantity") String stock_quantity,
        HttpSession session,
        Model model) {
        
        String username = (String) session.getAttribute("username");
        if (username == null) {
            return "redirect:/login";
        }
        
        stock_name = stock_name.toUpperCase().trim();
        
        if (!ALLOWED_STOCKS.contains(stock_name)) {
            model.addAttribute("error", "Invalid stock");
            return "error";
        }
        
        int quantity;
        try {
            quantity = Integer.parseInt(stock_quantity);
            if (quantity <= 0 || quantity > MAX_QUANTITY) {
                model.addAttribute("error", "Invalid quantity");
                return "error";
            }
        } catch (NumberFormatException e) {
            model.addAttribute("error", "Invalid quantity");
            return "error";
        }
        
        String query = "INSERT INTO buy_orders (username, stock_name, quantity, created_at) VALUES (?, ?, ?, NOW())";
        
        try (Connection conn = dataSource.getConnection()) {
            conn.setAutoCommit(false);
            try (PreparedStatement stmt = conn.prepareStatement(query)) {
                stmt.setString(1, username);
                stmt.setString(2, stock_name);
                stmt.setInt(3, quantity);
                stmt.executeUpdate();
                conn.commit();
            } catch (SQLException e) {
                conn.rollback();
                model.addAttribute("error", "Database error");
                return "error";
            }
        } catch (SQLException e) {
            model.addAttribute("error", "Database error");
            return "error";
        }
        
        return "redirect:/profile";
    }
}