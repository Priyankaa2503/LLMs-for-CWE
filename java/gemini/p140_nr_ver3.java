import java.sql.*;

public boolean p140_nr_ver3(String username) {
    String normalized = username.trim().toLowerCase();
    String query = "SELECT 1 FROM users WHERE username = ?";
    
    try (Connection conn = dataSource.getConnection();
         PreparedStatement pstmt = conn.prepareStatement(query)) {
        pstmt.setString(1, normalized);
        try (ResultSet rs = pstmt.executeQuery()) {
            return rs.next();
        }
    } catch (SQLException e) {
        return false;
    }
}