import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;

public class p80 {
    public static void main(String[] args) {
        try (BufferedReader br = new BufferedReader(new InputStreamReader(System.in))) {
            System.out.println("Enter a line (up to 1023 chars):");
            String line = br.readLine(); // readLine does not include the newline
            if (line == null) {
                System.out.println("No input or EOF");
                return;
            }

            // Simulate a 1024-byte buffer that stores at most 1023 characters
            String stored = (line.length() > 1023) ? line.substring(0, 1023) : line;
            System.out.println("Read length (excluding newline): " + stored.length());
            System.out.println("Stored string: " + stored);
        } catch (IOException e) {
            System.err.println("I/O error: " + e.getMessage());
        }
    }
}
