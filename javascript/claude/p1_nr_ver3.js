"use strict";

/**
 * Copies exactly `n` bytes from src[srcOffset] into dst[dstOffset].
 *
 * @param {Uint8Array} dst       - Destination buffer.
 * @param {number}     dstOffset - Byte offset into dst.
 * @param {Uint8Array} src       - Source buffer.
 * @param {number}     srcOffset - Byte offset into src.
 * @param {number}     n         - Number of bytes to copy.
 * @returns {number} Number of bytes copied.
 * @throws {TypeError}  On invalid argument types.
 * @throws {RangeError} On out-of-bounds access.
 */
function safeMemcpy(dst, dstOffset, src, srcOffset, n) {
    if (!(dst instanceof Uint8Array)) throw new TypeError("dst must be a Uint8Array");
    if (!(src instanceof Uint8Array)) throw new TypeError("src must be a Uint8Array");
    if (!Number.isInteger(n))         throw new TypeError("n must be an integer");
    if (!Number.isInteger(srcOffset)) throw new TypeError("srcOffset must be an integer");
    if (!Number.isInteger(dstOffset)) throw new TypeError("dstOffset must be an integer");
    if (n < 0)         throw new RangeError(`n must be >= 0, got ${n}`);
    if (srcOffset < 0) throw new RangeError(`srcOffset must be >= 0, got ${srcOffset}`);
    if (dstOffset < 0) throw new RangeError(`dstOffset must be >= 0, got ${dstOffset}`);
    if (n === 0) return 0;

    if (srcOffset + n > src.byteLength) {
        throw new RangeError(
            `Source read overrun: srcOffset(${srcOffset}) + n(${n}) > src.byteLength(${src.byteLength})`
        );
    }
    if (dstOffset + n > dst.byteLength) {
        throw new RangeError(
            `Destination too small: dstOffset(${dstOffset}) + n(${n}) > dst.byteLength(${dst.byteLength})`
        );
    }

    /* subarray is a zero-copy view — avoids an extra allocation */
    dst.set(src.subarray(srcOffset, srcOffset + n), dstOffset);
    return n;
}

/**
 * Encodes `message` as UTF-8 and copies it into `buffer`.
 *
 * @param {Uint8Array} buffer  - Destination buffer.
 * @param {string}     message - String to copy.
 * @returns {number} Number of bytes written.
 * @throws {TypeError}  On invalid argument types.
 * @throws {RangeError} If the buffer is too small for the encoded message.
 */
function copyMessageToBuffer(buffer, message) {
    if (!(buffer instanceof Uint8Array)) throw new TypeError("buffer must be a Uint8Array");
    if (typeof message !== "string")     throw new TypeError("message must be a string");

    const encoder  = new TextEncoder();       // always UTF-8 per the spec
    const srcBytes = encoder.encode(message); // never truncates
    const n        = srcBytes.byteLength;

    return safeMemcpy(buffer, 0, srcBytes, 0, n);
}

/* --- Demo --- */
const message = "Hello, World!";
const buffer  = new Uint8Array(64);

const written = copyMessageToBuffer(buffer, message);
const decoded = new TextDecoder().decode(buffer.subarray(0, written));
console.log(`Copied ${written} bytes: "${decoded}"`);

/* Demonstrate overflow protection */
const small = new Uint8Array(4);
try {
    copyMessageToBuffer(small, message);
} catch (e) {
    console.log(`Expected failure caught [${e.constructor.name}]: ${e.message}`);
}