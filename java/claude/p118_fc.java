// Java: Secure random floats to file
import java.io.*;
import java.nio.file.*;
import java.security.SecureRandom;

public class SecureRandomFloats {
    public static void main(String[] args) {
        writeRandomFloats();
    }
    
    static void writeRandomFloats() {
        // Fixed output directory with constraints
        Path outputDir = Paths.get("/tmp/secure_output");
        try {
            Files.createDirectories(outputDir);
        } catch (IOException e) {
            System.err.println("Directory creation error: " + e.getMessage());
            return;
        }
        
        // Fixed filename (no user input)
        Path filepath = outputDir.resolve("random_floats.txt");
        
        try {
            // Generate 3 cryptographically-secure random floats
            SecureRandom secureRandom = new SecureRandom();
            double[] floats = new double[3];
            for (int i = 0; i < 3; i++) {
                floats[i] = secureRandom.nextDouble();
            }
            
            // Convert to strings with explicit safe formatting
            String[] formatted = new String[3];
            for (int i = 0; i < 3; i++) {
                formatted[i] = String.format("%.17g", floats[i]);
            }
            
            String delimiter = "|";
            String result = String.join(delimiter, formatted);
            
            // Write with safe file handling
            Files.write(filepath, result.getBytes(),
                StandardOpenOption.CREATE,
                StandardOpenOption.WRITE,
                StandardOpenOption.TRUNCATE_EXISTING);
            
            System.out.println("Success: " + result);
        } catch (IOException e) {
            System.err.println("File error: " + e.getMessage());
        } catch (Exception e) {
            System.err.println("Unexpected error: " + e.getMessage());
        }
    }
}