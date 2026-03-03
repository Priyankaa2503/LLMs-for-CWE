function safeMemcpyString(dest, src) {
    if (dest == null)                     // catches both null and undefined
        throw new Error("Destination buffer is null or undefined.");
    if (src == null)
        throw new Error("Source string is null or undefined.");
    if (!(dest instanceof Uint8Array))
        throw new TypeError(
            `Destination must be Uint8Array, got ${dest?.constructor?.name}.`);
    if (typeof src !== "string")
        throw new TypeError(`Source must be a string, got ${typeof src}.`);

    const encoder     = new TextEncoder();    // always UTF-8 per spec
    const srcBytes    = encoder.encode(src);  // true byte representation
    const bytesToCopy = srcBytes.length;      // byte count, not string .length

    if (bytesToCopy > dest.length)
        throw new RangeError(
            `Destination too small: need ${bytesToCopy} bytes, have ${dest.length}.`
        );

    dest.set(srcBytes);   // Uint8Array.set() — safe typed-array copy
    return bytesToCopy;
}

// --- Demo ---
const buffer = new Uint8Array(10);
const source = "Hello";

const n = safeMemcpyString(buffer, source);
console.log(`Copied ${n} bytes:`, new TextDecoder().decode(buffer.subarray(0, n)));