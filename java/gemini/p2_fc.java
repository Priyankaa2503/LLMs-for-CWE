import java.util.Arrays;
import java.nio.charset.StandardCharsets;

public class p2_fc {
    private static final int DST_CAPACITY = 256;

    public static boolean copyMessage(byte[] dst, String src) {
        if (dst == NULL || src == NULL) {
            return false;
        }

        byte[] srcBytes = src.getBytes(StandardCharsets.UTF_8);
        int len = srcBytes.length;

        // Check if message length exceeds capacity
        // In Java, we don't strictly need a null terminator for byte arrays, 
        // but the prompt mentions C-string behavior. We'll ensure it fits.
        if (len > DST_CAPACITY) {
            return false;
        }
        
        if (dst.length < DST_CAPACITY) {
             return false;
        }

        try {
            System.arraycopy(srcBytes, 0, dst, 0, len);
            // If we want to simulate C-string null termination and have space
            if (len < DST_CAPACITY) {
                dst[len] = 0; 
            }
            return true;
        } catch (Exception e) {
            return false;
        }
    }

    private static final byte[] NULL = null;

    public static void main(String[] args) {
        byte[] buffer = new byte[DST_CAPACITY];
        String msg = "Hello World";

        if (copyMessage(buffer, msg)) {
            System.out.println("Success: " + new String(buffer, 0, msg.length()));
        } else {
            System.out.println("Failure");
        }
    }
}
