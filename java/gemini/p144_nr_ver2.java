import java.sql.*;
import java.util.concurrent.TimeUnit;

public class p144_nr_ver2 {
    public int manage(String email) {
        if (email == null || !email.contains("@")) return 0;

        String query = "SELECT id FROM users WHERE email = ?";
        try (Connection conn = DriverManager.getConnection("jdbc:sqlite:users.db");
             PreparedStatement pstmt = conn.prepareStatement(query)) {
            pstmt.setString(1, email);
            if (!pstmt.executeQuery().next()) return 0;

            ProcessBuilder pb = new ProcessBuilder("/usr/bin/php", "/var/www/scripts/unsubscribe.php", email);
            Process p = pb.start();
            if (!p.waitFor(5, TimeUnit.SECONDS)) { p.destroy(); return 0; }
            
            return (p.getInputStream().readAllBytes().toString().trim().equals("0")) ? 1 : 0;
        } catch (Exception e) {
            return 0;
        }
    }
}