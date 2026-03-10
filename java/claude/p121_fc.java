// Java - Type-Safe with Exception Handling
import java.nio.charset.StandardCharsets;

public class SecureMemoryCopy {
    private static final int MAX_BUFFER_SIZE = 256;
    
    public static boolean secureCopyAndPrint() {
        String source = "Secure memory copy example";
        
        try {
            // Validation: null check and size check
            if (source == null || source.isEmpty()) {
                System.err.println("Error: Invalid source string");
                return false;
            }
            
            if (source.length() > MAX_BUFFER_SIZE) {
                System.err.printf("Error: Source too large (%d > %d)%n", 
                                source.length(), MAX_BUFFER_SIZE);
                return false;
            }
            
            // Safe copy using immutable String
            String buffer = new String(source.getBytes(StandardCharsets.UTF_8), 
                                      StandardCharsets.UTF_8);
            
            // Verify copy
            if (buffer == null) {
                System.err.println("Error: Buffer creation failed");
                return false;
            }
            
            // Print data
            System.out.println("Buffer contents: " + buffer);
            System.out.println("Buffer length: " + buffer.length());
            
            // Garbage collection handles deallocation automatically
            // No explicit deallocation needed
            
            return true;
            
        } catch (OutOfMemoryError e) {
            System.err.println("Error: Memory allocation failed: " + e.getMessage());
            return false;
        } catch (Exception e) {
            System.err.println("Error: " + e.getMessage());
            return false;
        }
    }
    
    public static void main(String[] args) {
        boolean success = secureCopyAndPrint();
        System.exit(success ? 0 : 1);
    }
}