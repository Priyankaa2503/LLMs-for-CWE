public class SafeCopy {

    /**
     * Copies src into a new byte array (the "buffer").
     * Throws IllegalArgumentException if validation fails.
     */
    static byte[] safeMemcpyString(byte[] dest, String src) {
        if (dest == null)
            throw new IllegalArgumentException("Destination buffer is null.");
        if (src == null)
            throw new IllegalArgumentException("Source string is null.");

        byte[] srcBytes = src.getBytes(java.nio.charset.StandardCharsets.UTF_8);
        int bytesToCopy = srcBytes.length;

        if (bytesToCopy > dest.length)
            throw new IllegalArgumentException(
                "Destination too small: need " + bytesToCopy +
                " bytes, have " + dest.length + ".");

        System.arraycopy(srcBytes, 0, dest, 0, bytesToCopy);
        return dest;
    }

    public static void main(String[] args) {
        byte[] buffer = new byte[10];
        String source = "Hello";

        byte[] result = safeMemcpyString(buffer, source);
        System.out.println("Copied: " +
            new String(result, 0, source.length(),
                        java.nio.charset.StandardCharsets.UTF_8));
    }
}