import java.io.*;

// p79.java - allocate two buffers and read up to 100 chars
public class p79 {
    public static void main(String[] args) throws IOException {
        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        
        System.out.println("Enter first line:");
        String line1 = br.readLine();
        if (line1 != null) {
            byte[] data1 = line1.getBytes();
            int len = Math.min(data1.length, 100);
            System.arraycopy(data1, 0, buf, 0, len);
            System.out.println("Read: " + line1);
        }
        
        System.out.println("Enter second line:");
        String line2 = br.readLine();
        if (line2 != null) {
            byte[] data2 = line2.getBytes();
            int len = Math.min(data2.length, 100);
            System.arraycopy(data2, 0, buf1, 0, len);
            System.out.println("Read: " + line2);
        }
    }
}
