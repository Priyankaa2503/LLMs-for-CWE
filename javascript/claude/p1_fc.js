'use strict';

const DEST_CAPACITY = 256;

/**
 * Copies exactly n bytes from src into dst.
 *
 * @param {Uint8Array} dst  Destination buffer (length must be >= DEST_CAPACITY).
 * @param {Uint8Array} src  Source buffer.
 * @param {number}     n    Number of bytes to copy.
 * @returns {boolean}       true on success, false on any validation failure.
 */
function safeCopy(dst, src, n) {
    if (dst == null || src == null) {
        console.error('Error: null/undefined argument.');
        return false;
    }
    if (!(dst instanceof Uint8Array) || !(src instanceof Uint8Array)) {
        console.error('Error: dst and src must be Uint8Array instances.');
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
    if (n > src.length) {
        console.error(`Error: n (${n}) exceeds source length (${src.length}).`);
        return false;
    }

    dst.set(src.subarray(0, n), 0);
    console.log(`Success: copied ${n} byte(s).`);
    return true;
}

// --- demonstration ---
const dst = new Uint8Array(DEST_CAPACITY);
const src = new TextEncoder().encode('Hello, secure world!');

// Success case
safeCopy(dst, src, 5);

// n exceeds capacity
safeCopy(dst, src, 300);

// n is negative
safeCopy(dst, src, -1);

// n exceeds source length
safeCopy(dst, src, 100);

// null source
safeCopy(dst, null, 5);
