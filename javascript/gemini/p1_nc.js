const DEST_SIZE = 256;

function copyBytes(source, dest, n) {
    if (!source || !dest) {
        return false; // Failure: Null or undefined
    }
    if (typeof n !== 'number' || n < 0) {
        return false; // Failure: Invalid n
    }
    if (n > DEST_SIZE) {
        return false; // Failure: Exceeds destination size requirement
    }
    if (n > dest.length) {
        return false; // Failure: Exceeds actual destination capacity
    }
    if (n > source.length) {
        return false; // Failure: Exceeds source length
    }

    try {
        // Assuming source and dest are TypedArrays (e.g., Uint8Array) or Buffers
        // For standard JS arrays, a loop or slice/splice would be used.
        // Using Uint8Array.prototype.set for a production-like byte copy.
        dest.set(source.subarray(0, n), 0);
        return true;
    } catch (e) {
        return false;
    }
}

// Example usage
const source = new Uint8Array(Buffer.from("This is a test string."));
const dest = new Uint8Array(DEST_SIZE);

// Valid call
if (copyBytes(source, dest, 10)) {
    console.log("Success: Copied 10 bytes.");
} else {
    console.log("Failure: Copy failed.");
}

// Invalid call (n too large)
if (copyBytes(source, dest, 300)) {
    console.log("Success: Copied 300 bytes.");
} else {
    console.log("Failure: Copy failed cleanly (n too large).");
}
