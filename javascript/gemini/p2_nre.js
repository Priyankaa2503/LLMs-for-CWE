function copyMessage(dest, message, destCapacity) {
    // First check destination and source are valid
    if (!dest || !message) {
        return false; // Fail
    }

    // Compute n = length(message) safely
    // Assuming dest is a Buffer or Uint8Array
    const n = message.length;

    // Verify n is within the destination’s capacity
    if (n > destCapacity) {
        return false; // Fail
    }
    
    if (n > dest.length) {
        return false; // Fail
    }

    // Otherwise copy exactly n bytes and report success
    try {
        for (let i = 0; i < n; i++) {
            dest[i] = message.charCodeAt(i);
        }
        return true; // Success
    } catch (e) {
        return false;
    }
}
