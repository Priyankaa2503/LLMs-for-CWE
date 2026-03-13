import java.sql.*;
import java.util.regex.Pattern;
import java.io.*;
import java.util.concurrent.*;

public class p144_fc {
    private static final Pattern EMAIL_PATTERN = 
        Pattern.compile("^[A-Za-z0-9+_.-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");
    private static final String PHP_BIN = "/usr/bin/php";
    private static final int TIMEOUT_SECONDS = 5;
    
    /**
     * Securely unsubscribe an email with timeout and safety guarantees.
     * Returns: 1 if PHP script ran successfully,
     *          0 if email not found or execution failed
     */
    public static int unsubscribeEmail(String email, String dbUrl, 
                                       String phpScriptPath) {
        try {
            // Email validation and normalization
            if (email == null || email.length() > 254) {
                return 0;
            }
            
            String normalizedEmail = email.toLowerCase().trim();
            if (!EMAIL_PATTERN.matcher(normalizedEmail).matches()) {
                return 0;
            }
            
            // Database check with parameterized query
            boolean emailExists;
            try (Connection conn = DriverManager.getConnection(dbUrl);
                 PreparedStatement stmt = conn.prepareStatement(
                     "SELECT id FROM users WHERE email = ?")) {
                stmt.setString(1, normalizedEmail);
                try (ResultSet rs = stmt.executeQuery()) {
                    emailExists = rs.next();
                }
            }
            
            if (!emailExists) {
                return 0;
            }
            
            // Safe PHP invocation with timeout
            ProcessBuilder pb = new ProcessBuilder(PHP_BIN, phpScriptPath, 
                                                   normalizedEmail);
            pb.redirectErrorStream(true);
            pb.directory(new File("/tmp"));
            
            Process process = pb.start();
            
            // Enforce timeout
            boolean completed = process.waitFor(TIMEOUT_SECONDS, TimeUnit.SECONDS);
            
            if (!completed) {
                process.destroyForcibly();
                return 0;
            }
            
            int exitCode = process.exitValue();
            return exitCode == 0 ? 1 : 0;
            
        } catch (SQLException | IOException | InterruptedException e) {
            return 0;
        }
    }
}