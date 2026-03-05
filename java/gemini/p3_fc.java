import java.nio.charset.StandardCharsets;

public class p3_fc {
    private static final int DST_CAPACITY = 256;

    public static boolean copyHello(byte[] dst, String src, int n) {
        if (dst == NULL || src == NULL) {
            return false;
        }

        // Validate capacity
        if (n > DST_CAPACITY) {
            return false;
        }
        
        if (dst.length < DST_CAPACITY) {
            return false;
        }

        byte[] srcBytes = src.getBytes(StandardCharsets.UTF_8);
        
        // Validate source has enough bytes
        if (srcBytes.length < n) {
            return false;
        }

        try {
            System.arraycopy(srcBytes, 0, dst, 0, n);
            // Null terminate if possible
            if (n < dst.length) {
                dst[n] = 0;
            }
            return true;
        } catch (Exception e) {
            return false;
        }
    }

    private static final byte[] NULL = null;

    public static void main(String[] args) {
        byte[] buffer = new byte[DST_CAPACITY];
        String hello = "Hello";
        int len = hello.length(); // Assuming ASCII/UTF-8 single byte chars for "Hello"

        if (copyHello(buffer, hello, len)) {
            System.out.println("Copied: " + new String(buffer, 0, len));
        } else {
            System.out.println("Failed to copy");
        }
    }
}
