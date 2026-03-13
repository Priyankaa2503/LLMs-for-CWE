// Java with JDBC
import java.sql.*;
import java.util.concurrent.*;
import java.util.regex.Pattern;

public class p144_nre {
    private static final Pattern EMAIL_PATTERN = 
        Pattern.compile("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    private static final String PHP_SCRIPT = "/opt/app/unsub.php";
    private static final long TIMEOUT_MS = 5000;
    
    private String dbUrl;
    private String dbUser;
    private String dbPassword;

    public EmailUnsubscriber(String dbUrl, String dbUser, String dbPassword) {
        this.dbUrl = dbUrl;
        this.dbUser = dbUser;
        this.dbPassword = dbPassword;
    }

    private String validateEmail(String email) {
        if (email == null || email.length() > 254) {
            return null;
        }
        String normalized = email.trim().toLowerCase();
        return EMAIL_PATTERN.matcher(normalized).matches() ? normalized : null;
    }

    public int checkAndUnsubscribe(String email) {
        email = validateEmail(email);
        if (email == null) {
            return 0;
        }

        try (Connection conn = DriverManager.getConnection(dbUrl, dbUser, dbPassword)) {
            String query = "SELECT 1 FROM emails WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(query)) {
                stmt.setString(1, email);
                try (ResultSet rs = stmt.executeQuery()) {
                    if (!rs.next()) {
                        return 0;
                    }
                }
            }

            return executePhpScript(email);
        } catch (SQLException e) {
            return 0;
        }
    }

    private int executePhpScript(String email) {
        try {
            ProcessBuilder pb = new ProcessBuilder("/usr/bin/php", PHP_SCRIPT, email);
            pb.redirectErrorStream(true);
            Process process = pb.start();
            
            boolean finished = process.waitFor(TIMEOUT_MS, TimeUnit.MILLISECONDS);
            if (!finished) {
                process.destroy();
                return 0;
            }

            return process.exitValue() == 0 ? 1 : 0;
        } catch (Exception e) {
            return 0;
        }
    }
}