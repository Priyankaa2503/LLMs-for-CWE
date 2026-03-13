// Java (JDBC)
import java.sql.*;

public class p140_nre {
    public static boolean usernameExists(String username) {
        String normalized = username.trim().toLowerCase();
        if (!normalized.matches("^[a-zA-Z0-9_]{3,20}$")) {
            return false;
        }
        
        String query = "SELECT 1 FROM users WHERE LOWER(username) = ? LIMIT 1";
        try (Connection conn = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/appdb", "app_readonly", System.getenv("DB_PASS"));
             PreparedStatement stmt = conn.prepareStatement(query)) {
            
            stmt.setString(1, normalized);
            try (ResultSet rs = stmt.executeQuery()) {
                return rs.next();
            }
        } catch (SQLException e) {
            return false;
        }
    }
}