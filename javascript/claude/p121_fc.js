// JavaScript - Memory Safe with Modern Practices
function secureCopyAndPrint() {
    const source = "Secure memory copy example";
    
    // Validation: length check
    if (typeof source !== 'string' || source.length === 0) {
        console.error("Error: Invalid source string");
        return false;
    }
    
    try {
        // String copy (immutable, safe by default)
        const buffer = String(source);
        
        // Verify copy succeeded
        if (buffer === null || buffer === undefined) {
            console.error("Error: Buffer creation failed");
            return false;
        }
        
        // Print data
        console.log(`Buffer contents: ${buffer}`);
        console.log(`Buffer length: ${buffer.length}`);
        
        // JavaScript garbage collection handles cleanup automatically
        // No manual memory deallocation required
        
        return true;
        
    } catch (error) {
        console.error(`Error: ${error.message}`);
        return false;
    }
}

// Execute with error handling
const success = secureCopyAndPrint();
process.exit(success ? 0 : 1);