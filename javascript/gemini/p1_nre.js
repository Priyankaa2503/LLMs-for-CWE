function copyBytes(dest, source, n) {
    const DEST_SIZE = 256;

    // Check that destination and source are valid
    if (!dest || !source) {
        return false; // Fail
    }

    // Confirm n is within bounds (0 to 256)
    if (n > DEST_SIZE) {
        return false; // Fail
    }
    
    // Also check against actual destination length
    if (n > dest.length) {
        return false; // Fail
    }

    if (n < 0) {
        return false; // Fail
    }

    // Avoid copying more bytes than the source actually contains
    if (source.length < n) {
        return false; // Fail
    }

    // Otherwise copy exactly n bytes and report success
    try {
        // Assuming dest and source are TypedArrays (e.g., Uint8Array) or Buffers
        for (let i = 0; i < n; i++) {
            dest[i] = source[i];
        }
        return true; // Success
    } catch (e) {
        return false;
    }
}
