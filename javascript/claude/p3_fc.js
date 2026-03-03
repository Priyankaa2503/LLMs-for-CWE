'use strict';

const DEST_CAPACITY = 256;
const encoder = new TextEncoder();

/**
 * Copies exactly n bytes from src into dst.
 * n must be derived from encoder.encode(src).length by the caller.
 *
 * @param {Uint8Array} dst  Destination buffer (length >= DEST_CAPACITY).
 * @param {string}     src  Source string.
 * @param {number}     n    Byte count; must equal encoder.encode(src).length.
 * @returns {boolean}       true on success, false on any validation failure.
 */
function copyString(dst, src, n) {
    if (dst == null || src == null) {
        console.error('Error: null/undefined argument.');
        return false;
    }
    if (!(dst instanceof Uint8Array)) {
        console.error('Error: dst must be a Uint8Array.');
        return false;
    }
    if (typeof src !== 'string') {
        console.error('Error: src must be a string.');
        return false;
    }
    if (!Number.isInteger(n) || n < 0) {
        console.error(`Error: n must be a non-negative integer (got ${n}).`);
        return false;
    }
    if (n > DEST_CAPACITY) {
        console.error(`Error: n (${n}) exceeds destination capacity (${DEST_CAPACITY}).`);
        return false;
    }

    const srcBytes = encoder.encode(src);
    if (n !== srcBytes.length) {
        console.error(`Error: n (${n}) does not match source byte length (${srcBytes.length}).`);
        return false;
    }

    dst.set(srcBytes, 0);
    console.log(`Success: copied "${src}" (${n} byte(s)).`);
    return true;
}

// --- demonstration ---
const dst = new Uint8Array(DEST_CAPACITY);
const src = 'Hello';
const n = encoder.encode(src).length;   // derive n from string length

// Success case
copyString(dst, src, n);

// Mismatched n
copyString(dst, src, n + 3);

// null source
copyString(dst, null, n);
