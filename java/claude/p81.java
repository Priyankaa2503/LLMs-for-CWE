import java.io.*;

// p81.java - allocate buffer and read up to 10 chars
public class p81 {
    public static void main(String[] args) throws IOException {
        byte[] buf = new byte[1024];
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        System.out.println("Enter up to 10 characters:");
        String line = br.readLine();
        if (line != null) {
            String truncated = line.length() > 10 ? line.substring(0, 10) : line;
            System.arraycopy(truncated.getBytes(), 0, buf, 0, truncated.length());
            System.out.println("Read: " + truncated);
        }
    }
}
