import java.sql.*;

public class Unsubscribe Service {
    public void unsubscribeUser(String email) {
        String url = "jdbc:mysql://localhost:3306/db";
        String sql = "DELETE FROM subscribers WHERE email = ?";

        try (Connection conn = DriverManager.getConnection(url, "user", "pass");
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            
            pstmt.setString(1, email);
            int rowsDeleted = pstmt.executeUpdate();

            if (rowsDeleted > 0) {
                System.out.println("Email removed successfully.");
            } else {
                System.out.println("Email not found in database.");
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }
}