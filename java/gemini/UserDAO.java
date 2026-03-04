import java.sql.*;

public class UserDAO {
    public boolean checkUsernameExists(String username) {
        String url = "jdbc:mysql://localhost:3306/mydb";
        String query = "SELECT 1 FROM users WHERE username = ?";

        try (Connection conn = DriverManager.getConnection(url, "user", "pass");
             PreparedStatement stmt = conn.prepareStatement(query)) {
            
            stmt.setString(1, username);
            try (ResultSet rs = stmt.executeQuery()) {
                return rs.next(); // Returns true if a record is found
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }
}