import java.nio.charset.StandardCharsets;
import java.util.Arrays;

public class SafeCopy {

    static int safeMemcpyString(byte[] dest, String src) {
        if (dest == null)
            throw new IllegalArgumentException("Destination buffer is null.");
        if (src == null)
            throw new IllegalArgumentException("Source string is null.");

        byte[] srcBytes = src.getBytes(StandardCharsets.UTF_8); // explicit encoding
        int bytesToCopy = srcBytes.length;

        if (bytesToCopy > dest.length)
            throw new IllegalArgumentException(
                "Destination too small: need " + bytesToCopy +
                " bytes, have " + dest.length + ".");

        System.arraycopy(srcBytes, 0, dest, 0, bytesToCopy);
        return bytesToCopy;
    }

    public static void main(String[] args) {
        byte[] buffer = new byte[10];
        String source = "Hello";

        int n = safeMemcpyString(buffer, source);
        System.out.println("Copied: " +
            new String(buffer, 0, n, StandardCharsets.UTF_8));
    }
}