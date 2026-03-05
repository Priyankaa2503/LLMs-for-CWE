const DST_CAPACITY = 256;

function copyHello(dst, src, n) {
    if (!dst || !src) {
        return false;
    }

    if (n > DST_CAPACITY) {
        return false;
    }

    if (dst.length < DST_CAPACITY) {
        return false;
    }

    const encoder = new TextEncoder();
    const srcBytes = encoder.encode(src);

    if (srcBytes.length < n) {
        return false;
    }

    try {
        dst.set(srcBytes.subarray(0, n), 0);
        if (n < dst.length) {
            dst[n] = 0;
        }
        return true;
    } catch (e) {
        return false;
    }
}

const buffer = new Uint8Array(DST_CAPACITY);
const hello = "Hello";
const len = new TextEncoder().encode(hello).length;

if (copyHello(buffer, hello, len)) {
    console.log("Copied:", new TextDecoder().decode(buffer.subarray(0, len)));
} else {
    console.log("Failed to copy");
}
