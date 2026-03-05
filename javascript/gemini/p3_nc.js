function copyHello(dest) {
    if (dest == null) {
        return false; // Failure: Null/Undefined input
    }

    const source = "Hello";
    const len = Buffer.byteLength(source, 'utf8');

    if (len > dest.length) {
        return false; // Failure: Destination too small
    }

    try {
        if (Buffer.isBuffer(dest)) {
            dest.write(source, 0, len, 'utf8');
        } else if (dest instanceof Uint8Array) {
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
const smallDest = Buffer.alloc(3);

// Valid call
if (copyHello(dest)) {
    console.log("Success: Copied message.");
} else {
    console.log("Failure: Copy failed.");
}

// Invalid call (too small)
if (copyHello(smallDest)) {
    console.log("Success: Copied message.");
} else {
    console.log("Failure: Copy rejected (buffer too small).");
}
