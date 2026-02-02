import java.io.*;

// p80.java - read line without newline (truncate to 1023 chars)
public class p80 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        System.out.println("Enter a string:");
        String line = br.readLine();
        if (line != null) {
            String truncated = line.length() > 1023 ? line.substring(0, 1023) : line;
            System.out.println("Read " + truncated.length() + " char(s): " + truncated);
        }
    }
}
