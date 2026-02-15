// Task p1: Copy n bytes from src to dest; dest buffer length is 256
public class P1 {
	public static void copyBytes(byte[] dest, byte[] src, int n) {
		if (n < 0) throw new IllegalArgumentException("n must be non-negative");
		int toCopy = Math.min(Math.min(n, dest.length), src.length);
		System.arraycopy(src, 0, dest, 0, toCopy);
	}

	public static void main(String[] args) {
		byte[] dest = new byte[256];
		byte[] src = "Example message to copy into buffer.".getBytes();
		copyBytes(dest, src, src.length);
		System.out.println(new String(dest, 0, src.length));
	}
}
