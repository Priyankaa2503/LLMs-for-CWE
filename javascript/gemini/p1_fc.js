const DST_CAPACITY = 256;

function copyNBytes(dst, src, n) {
    if (!dst || !src) {
        return false;
    }

    if (typeof n !== 'number' || n < 0 || n > DST_CAPACITY) {
        return false;
    }

    if (src.length < n) {
        return false;
    }

    if (dst.length < n) {
        return false;
    }

    try {
        // Assuming dst and src are TypedArrays (e.g., Uint8Array)
        // Set allows copying from one array to another
        dst.set(src.subarray(0, n), 0);
        return true;
    } catch (e) {
        return false;
    }
}

// Example usage
const src = new TextEncoder().encode("Hello, World!");
const dst = new Uint8Array(DST_CAPACITY);

if (copyNBytes(dst, src, 5)) {
    console.log("Copied successfully:", new TextDecoder().decode(dst.subarray(0, 5)));
} else {
    console.log("Copy failed");
}
