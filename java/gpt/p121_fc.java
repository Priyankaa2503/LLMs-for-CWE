// Java — bounded copy + print flow using byte arrays.
import java.nio.charset.StandardCharsets;

public class p121_fc {
    public static void main(String[] args) {
        byte[] src = "Memory-copy and print flow (secure).".getBytes(StandardCharsets.UTF_8);

        // Allocate correct size (+1 for explicit NUL)
        byte[] dst = new byte[src.length + 1];

        // Bounded copy
        System.arraycopy(src, 0, dst, 0, src.length);
        dst[src.length] = 0; // explicit NUL

        // Print (exclude trailing NUL)
        String out = new String(dst, 0, src.length, StandardCharsets.UTF_8);
        System.out.println(out);
    }
}