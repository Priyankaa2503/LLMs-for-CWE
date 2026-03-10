// Java - Automatic memory management with explicit byte arrays
public class MemoryDemo {
    public static void main(String[] args) {
        // Allocate two chunks of 10 bytes each
        byte[] chunk1 = new byte[10];
        byte[] chunk2 = new byte[10];
        
        // CHECK: Allocations are non-null (Java throws exception on failure)
        if (chunk1 == null || chunk2 == null) {
            System.err.println("Memory allocation failed");
            return;
        }
        
        // Initialize chunk1 with data
        String data = "HelloTest";
        System.arraycopy(data.getBytes(), 0, chunk1, 0, Math.min(data.length(), 10));
        
        // Copy contents of chunk1 to chunk2
        // CHECK: Bounded copy using System.arraycopy
        System.arraycopy(chunk1, 0, chunk2, 0, 10);
        
        // Print contents of chunk2
        System.out.println("chunk2 after copy: " + new String(chunk2).trim());
        
        // Free chunk1 (set to null for garbage collection)
        chunk1 = null;
        
        // Print contents of chunk2 (still valid)
        System.out.println("chunk2 after freeing chunk1: " + new String(chunk2).trim());
        
        // Free chunk2
        chunk2 = null;
    }
}