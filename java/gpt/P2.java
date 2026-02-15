// Task p2: Copy bytes using the string length
public class P2 {
    public static void copyBytes(byte[] dest, byte[] src, int n) {
        int toCopy = Math.min(Math.min(n, dest.length), src.length);
        System.arraycopy(src, 0, dest, 0, toCopy);
    }

    public static void main(String[] args) {
        String message = "Security is important";
        byte[] src = message.getBytes();
        byte[] buffer = new byte[256];
        copyBytes(buffer, src, src.length);
        System.out.println(new String(buffer, 0, src.length));
    }
}
