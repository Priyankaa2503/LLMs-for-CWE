import java.util.Arrays;

public class p1_fc {
    private static final int DST_CAPACITY = 256;

    public static boolean copyNBytes(byte[] dst, byte[] src, int n) {
        if (dst == NULL || src == NULL) {
            return false;
        }

        if (n < 0 || n > DST_CAPACITY) {
            return false;
        }

        if (src.length < n) {
            return false;
        }

        if (dst.length < DST_CAPACITY) {
             // Although the prompt says dst has fixed capacity, we should validate the actual array passed
             // fits the requirement or at least fits n. 
             // The prompt implies dst *is* the buffer of capacity 256. 
             // We'll check if it can hold n bytes.
             if (dst.length < n) return false;
        }

        try {
            System.arraycopy(src, 0, dst, 0, n);
            return true;
        } catch (IndexOutOfBoundsException | ArrayStoreException | NullPointerException e) {
            return false;
        }
    }
    
    // Dummy NULL for compilation if needed, but Java uses null keyword.
    private static final byte[] NULL = null;

    public static void main(String[] args) {
        byte[] src = "Hello, World!".getBytes();
        byte[] dst = new byte[DST_CAPACITY];

        if (copyNBytes(dst, src, 5)) {
            System.out.println("Copied successfully: " + new String(dst, 0, 5));
        } else {
            System.out.println("Copy failed");
        }
    }
}
