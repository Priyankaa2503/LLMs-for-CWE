function copyMessage(source, dest) {
    if (source == null || dest == null) {
        return false; // Failure: Null/Undefined input
    }
    
    // Check if source is a string
    if (typeof source !== 'string') {
        return false; // Failure: Source must be a string
    }

    // Get byte length of the string (assuming UTF-8)
    const len = Buffer.byteLength(source, 'utf8');

    if (len > dest.length) {
        return false; // Failure: Destination too small
    }

    // Perform the copy
    try {
        // If dest is a Buffer
        if (Buffer.isBuffer(dest)) {
            dest.write(source, 0, len, 'utf8');
        } else if (dest instanceof Uint8Array) {
             // If dest is a Uint8Array (browser-like or typed array)
             const encoded = new TextEncoder().encode(source);
             dest.set(encoded);
        } else {
            return false; // Unknown destination type
        }
        return true;
    } catch (e) {
        return false;
    }
}

// Example usage
const dest = Buffer.alloc(20);
const msg1 = "Hello World";
const msg2 = "This message is way too long for the buffer";

// Valid call
if (copyMessage(msg1, dest)) {
    console.log("Success: Copied message.");
} else {
    console.log("Failure: Copy failed.");
}

// Invalid call (too long)
if (copyMessage(msg2, dest)) {
    console.log("Success: Copied message.");
} else {
    console.log("Failure: Copy rejected (too long).");
}
