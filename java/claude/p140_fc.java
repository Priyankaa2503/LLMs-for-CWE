// Java (JDBC with error containment)
import java.sql.*;

public class p140_fc {
    private static final String DB_URL = System.getenv("DB_URL");
    private static final String DB_USER = System.getenv("DB_USER");
    private static final String DB_PASS = System.getenv("DB_PASS");
    
    public static boolean usernameExists(String username) {
        // Normalize: trim and validate format
        username = username.trim();
        if (!username.matches("^[a-zA-Z0-9_]{3,32}$")) {
            return false;
        }
        
        String query = "SELECT 1 FROM users WHERE username = ? LIMIT 1";
        
        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASS);
             PreparedStatement stmt = conn.prepareStatement(query)) {
            
            // Parameterized query
            stmt.setString(1, username);
            
            try (ResultSet rs = stmt.executeQuery()) {
                return rs.next();
            }
            
        } catch (SQLException e) {
            // Log internally without exposing SQL details
            System.err.println("Database query failed");
            return false;
        }
    }
}