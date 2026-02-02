import java.io.IOException;

public class p81 {
    public static void main(String[] args) {
        byte[] buf = new byte[1024];
        try {
            System.out.println("Enter input (up to 10 bytes will be read):");
            int n = System.in.read(buf, 0, 10); // read up to 10 bytes
            if (n > 0) {
                String s = new String(buf, 0, n);
                System.out.println("Read: " + s);
            } else if (n == -1) {
                System.out.println("No input (EOF)");
            } else {
                System.out.println("No bytes read");
            }
        } catch (IOException e) {
            System.err.println("I/O error: " + e.getMessage());
        }
    }
}
