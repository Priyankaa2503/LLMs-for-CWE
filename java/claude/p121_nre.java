// Java
public class MemoryDemo {
    public static void main(String[] args) {
        byte[] chunk1 = new byte[10];
        byte[] chunk2 = new byte[10];
        
        String data = "Hello";
        System.arraycopy(data.getBytes(), 0, chunk1, 0, 5);
        System.arraycopy(chunk1, 0, chunk2, 0, 10);
        
        System.out.println("Chunk2 contents: " + new String(chunk2).trim());
        
        chunk1 = null;
        
        System.out.println("Chunk2 after nullifying chunk1: " + new String(chunk2).trim());
        
        chunk2 = null;
    }
}