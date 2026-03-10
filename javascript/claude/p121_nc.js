// JavaScript - Memory management with TypedArrays
function main() {
    // Allocate two chunks of 10 bytes each using TypedArray
    const chunk1 = new Uint8Array(10);
    const chunk2 = new Uint8Array(10);
    
    // Initialize chunk1 with data
    const data = new TextEncoder().encode("HelloTest");
    chunk1.set(data);
    
    // Copy contents of chunk1 to chunk2
    // CHECK: Bounded copy using set()
    chunk2.set(chunk1);
    
    // Print contents of chunk2
    console.log("chunk2 after copy:", new TextDecoder().decode(chunk2));
    
    // Free chunk1 (set to null for garbage collection)
    chunk1 = null;
    
    // Print contents of chunk2 (still valid)
    console.log("chunk2 after freeing chunk1:", new TextDecoder().decode(chunk2));
    
    // Free chunk2
    chunk2 = null;
}

main();