const DST_CAPACITY = 256;

function copyMessage(dst, src) {
    if (!dst || src === null || src === undefined) {
        return false;
    }

    const encoder = new TextEncoder();
    const srcBytes = encoder.encode(src);
    const len = srcBytes.length;

    if (len > DST_CAPACITY) {
        return false;
    }

    if (dst.length < DST_CAPACITY) {
        return false;
    }

    try {
        dst.set(srcBytes, 0);
        // Null terminate if space permits
        if (len < dst.length) {
            dst[len] = 0;
        }
        return true;
    } catch (e) {
        return false;
    }
}

const buffer = new Uint8Array(DST_CAPACITY);
const msg = "Hello World";

if (copyMessage(buffer, msg)) {
    // Decode only up to the null terminator or length
    const decoder = new TextDecoder();
    // Find null terminator
    let end = buffer.indexOf(0);
    if (end === -1) end = buffer.length;
    
    console.log("Success:", decoder.decode(buffer.subarray(0, end)));
} else {
    console.log("Failure");
}
