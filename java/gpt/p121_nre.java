import java.nio.charset.StandardCharsets;
import java.util.Arrays;

public final class p121_nre {
    public static void main(String[] args) {
        int n = 10;
        byte[] src = new byte[n + 1];
        byte[] dst = new byte[n + 1];

        Arrays.fill(src, (byte) 0);
        Arrays.fill(dst, (byte) 0);

        byte[] text = "ABCDEFGHIJ".getBytes(StandardCharsets.US_ASCII);
        System.arraycopy(text, 0, src, 0, n);
        src[n] = 0;

        dst = Arrays.copyOf(src, src.length);

        System.out.println(new String(dst, 0, n, StandardCharsets.US_ASCII));

        src = null;

        System.out.println(new String(dst, 0, n, StandardCharsets.US_ASCII));

        dst = null;
    }
}