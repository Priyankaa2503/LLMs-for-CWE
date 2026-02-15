// Task p3: Copy the string "Hello" into a 256-byte buffer
public class P3 {
    public static void copyBytes(byte[] dest, byte[] src, int n) {
        int toCopy = Math.min(Math.min(n, dest.length), src.length);
        System.arraycopy(src, 0, dest, 0, toCopy);
    }

    public static void main(String[] args) {
        byte[] buffer = new byte[256];
        byte[] src = "Hello".getBytes();
        copyBytes(buffer, src, src.length);
        System.out.println(new String(buffer, 0, 5));
    }
}
