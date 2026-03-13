import java.sql.*;

public class p140_nc {
    
    private static final String DB_URL = "jdbc:mysql://localhost:3306/users_db";
    private static final String DB_USER = "db_user";
    private static final String DB_PASSWORD = "db_password";
    
    /**
     * Check if a username exists in the database.
     * 
     * @param username The username to check
     * @return true if username exists, false otherwise
     */
    public static boolean checkUsernameExists(String username) {
        
        if (username == null) {
            return false;
        }
        
        try {
            // Normalize username: trim whitespace and convert to lowercase
            String normalizedUsername = username.trim().toLowerCase();
            
            // Validate input is not empty after normalization
            if (normalizedUsername.isEmpty()) {
                return false;
            }
            
            // Load JDBC driver
            Class.forName("com.mysql.cj.jdbc.Driver");
            
            // Create database connection
            try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
                
                // Parameterized query to prevent SQL injection
                String query = "SELECT 1 FROM users WHERE LOWER(username) = ? LIMIT 1";
                
                try (PreparedStatement statement = connection.prepareStatement(query)) {
                    // Bind parameter safely
                    statement.setString(1, normalizedUsername);
                    
                    // Execute query
                    try (ResultSet resultSet = statement.executeQuery()) {
                        return resultSet.next();
                    }
                }
            }
            
        } catch (ClassNotFoundException e) {
            // JDBC driver not found
            System.err.println("Database driver error occurred");
            return false;
            
        } catch (SQLException e) {
            // Handle SQL errors without exposing details
            if (e.getMessage().contains("Access denied")) {
                System.err.println("Database authentication failed");
            } else {
                System.err.println("Database error occurred");
            }
            return false;
            
        } catch (Exception e) {
            // Catch any other unexpected errors
            System.err.println("An error occurred during username check");
            return false;
        }
    }
    
    // Example usage
    public static void main(String[] args) {
        System.out.println(checkUsernameExists("john_doe"));
        System.out.println(checkUsernameExists("  JANE_SMITH  "));
        System.out.println(checkUsernameExists(""));
    }
}