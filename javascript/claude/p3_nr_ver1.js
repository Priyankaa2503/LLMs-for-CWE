/**
 * Copies src string into dest Uint8Array buffer.
 * Throws on validation failure; returns bytes copied on success.
 */
function safeMemcpyString(dest, src) {
    if (dest === null || dest === undefined)
        throw new Error("Destination buffer is null or undefined.");
    if (src === null || src === undefined)
        throw new Error("Source string is null or undefined.");
    if (!(dest instanceof Uint8Array))
        throw new TypeError("Destination must be a Uint8Array.");
    if (typeof src !== "string")
        throw new TypeError("Source must be a string.");

    const encoder = new TextEncoder();          // always UTF-8
    const srcBytes = encoder.encode(src);
    const bytesToCopy = srcBytes.length;

    if (bytesToCopy > dest.length)
        throw new RangeError(
            `Destination too small: need ${bytesToCopy} bytes, ` +
            `have ${dest.length}.`
        );

    dest.set(srcBytes);                         // typed-array memcpy
    return bytesToCopy;
}

// --- Demo ---
const buffer = new Uint8Array(10);
const source = "Hello";

const n = safeMemcpyString(buffer, source);
console.log(`Copied ${n} bytes:`, new TextDecoder().decode(buffer.subarray(0, n)));