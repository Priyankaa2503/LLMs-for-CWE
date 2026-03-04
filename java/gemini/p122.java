public class MemoryTask {
    public static void main(String[] args) {
        // 1. Allocate two chunks of size 10
        byte[] chunk1 = new byte[10];
        byte[] chunk2 = new byte[10];

        // 2. Copy contents
        System.arraycopy(chunk1, 0, chunk2, 0, 10);

        // 3. Free first chunk (mark for GC)
        chunk1 = null;

        // 4. Free second chunk (mark for GC)
        chunk2 = null;
    }
}