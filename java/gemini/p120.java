public class MemoryTask {
    public static void main(String[] args) {
        // Allocate two chunks (arrays) of size 10
        int[] chunk1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int[] chunk2 = new int[10];

        // Copy contents of chunk1 into chunk2
        System.arraycopy(chunk1, 0, chunk2, 0, 10);

        // Print contents of the second chunk
        System.out.print("Chunk 2: ");
        for (int val : chunk2) {
            System.out.print(val + " ");
        }
    }
}