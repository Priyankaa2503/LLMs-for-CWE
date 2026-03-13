import java.sql.*;
import java.util.regex.Pattern;
import java.io.*;

public class p144_nc {
    private static final String DB_PATH = "jdbc:sqlite:/path/to/database.db";
    private static final String PHP_SCRIPT = "/path/to/unsubscribe.php";
    private static final int TIMEOUT_SECONDS = 5;
    private static final Pattern EMAIL_PATTERN = 
        Pattern.compile("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");

    public static String validateEmail(String email) {
        String normalized = email.trim().toLowerCase();
        if (EMAIL_PATTERN.matcher(normalized).matches() && normalized.length() <= 254) {
            return normalized;
        }
        return null;
    }

    public static int checkAndUnsubscribe(String email) {
        String normalizedEmail = validateEmail(email);
        if (normalizedEmail == null) {
            return 0;
        }

        try {
            Class.forName("org.sqlite.JDBC");
            Connection conn = DriverManager.getConnection(DB_PATH);
            
            String query = "SELECT 1 FROM users WHERE email = ?";
            PreparedStatement pstmt = conn.prepareStatement(query);
            pstmt.setString(1, normalizedEmail);
            
            ResultSet rs = pstmt.executeQuery();
            boolean exists = rs.next();
            rs.close();
            pstmt.close();
            conn.close();
            
            if (!exists) {
                return 0;
            }

            int result = callPhpScript(normalizedEmail);
            return result;

        } catch (Exception e) {
            return 0;
        }
    }

    private static int callPhpScript(String email) {
        try {
            ProcessBuilder pb = new ProcessBuilder("/usr/bin/php", PHP_SCRIPT, email);
            pb.redirectErrorStream(true);
            Process process = pb.start();

            StringBuilder output = new StringBuilder();
            BufferedReader reader = new BufferedReader(
                new InputStreamReader(process.getInputStream())
            );
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line);
            }

            boolean finished = process.waitFor(TIMEOUT_SECONDS, java.util.concurrent.TimeUnit.SECONDS);
            
            if (!finished) {
                process.destroyForcibly();
                return 0;
            }

            if (process.exitValue() != 0) {
                return 0;
            }

            return output.toString().trim().equals("0") ? 1 : 0;

        } catch (Exception e) {
            return 0;
        }
    }

    public static void main(String[] args) {
        int result = checkAndUnsubscribe("user@example.com");
        System.out.println(result);
    }
}