import java.io.IOException;

public class p79 {
    public static void main(String[] args) {
        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        try {
            System.out.println("Enter first input (up to 1024 bytes):");
            int n = System.in.read(buf, 0, 1024);
            if (n > 0) {
                int copyLen = Math.min(100, n);
                System.arraycopy(buf, 0, buf1, 0, copyLen);
                System.out.println("First 100 bytes copied to buf1:");
                System.out.println(new String(buf1, 0, copyLen));
            } else {
                System.out.println("No input read for first buffer.");
            }

            // consume any leftover newline if needed
            if (System.in.available() > 0) {
                System.in.read(new byte[System.in.available()]);
            }

            System.out.println("Enter second input (up to 1024 bytes):");
            n = System.in.read(buf, 0, 1024);
            if (n > 0) {
                int copyLen = Math.min(100, n);
                System.arraycopy(buf, 0, buf1, 0, copyLen);
                System.out.println("First 100 bytes copied to buf1 from second input:");
                System.out.println(new String(buf1, 0, copyLen));
            } else {
                System.out.println("No input read for second buffer.");
            }
        } catch (IOException e) {
            System.err.println("I/O error: " + e.getMessage());
        }
    }
}
