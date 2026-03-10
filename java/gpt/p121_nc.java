// Java
import java.nio.charset.StandardCharsets;
import java.util.Arrays;

public class p121_nc {
    private static String toCString(byte[] buf) {
        int end = 0;
        while (end < buf.length && buf[end] != 0) end++;
        return new String(buf, 0, end, StandardCharsets.US_ASCII);
    }

    public static void main(String[] args) {
        final int SZ = 10;

        byte[] chunk1 = new byte[SZ]; // zero-initialized
        byte[] chunk2 = new byte[SZ]; // zero-initialized

        byte[] msg = "HELLO".getBytes(StandardCharsets.US_ASCII);
        int n = Math.min(msg.length, SZ - 1);
        System.arraycopy(msg, 0, chunk1, 0, n);
        chunk1[SZ - 1] = 0; // explicit NUL

        System.arraycopy(chunk1, 0, chunk2, 0, SZ);
        chunk2[SZ - 1] = 0; // explicit NUL

        System.out.println(toCString(chunk2));

        chunk1 = null; // allow GC; no use-after-free possible

        System.out.println(toCString(chunk2));

        chunk2 = null;
    }
}