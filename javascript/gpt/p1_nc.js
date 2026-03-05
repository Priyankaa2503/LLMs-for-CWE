'use strict';

/**
 * p1_nc.js - Safe fixed-size buffer copy (JavaScript)
 *
 * Copies exactly n bytes from a source Uint8Array into a 256-byte
 * destination buffer with basic validation.
 */

const DEST_CAPACITY = 256;

/**
 * Copy exactly n bytes from src into dst.
 *
 * @param {Uint8Array} dst Destination buffer (length must be >= DEST_CAPACITY).
 * @param {Uint8Array} src Source buffer (must be non-null/defined).
 * @param {number} n      Number of bytes to copy.
 * @returns {{ success: boolean, error?: string }} Result of the operation.
 */
function copyNBytes(dst, src, n) {
    if (dst == null || src == null) {
        const error = 'destination and source must not be null/undefined.';
        console.error(`Error: ${error}`);
        return { success: false, error };
    }

    if (!(dst instanceof Uint8Array) || !(src instanceof Uint8Array)) {
        const error = 'dst and src must be Uint8Array instances.';
        console.error(`Error: ${error}`);
        return { success: false, error };
    }

    if (!Number.isInteger(n) || n < 0) {
        const error = `n must be a non-negative integer (got ${n}).`;
        console.error(`Error: ${error}`);
        return { success: false, error };
    }

    if (dst.length < DEST_CAPACITY) {
        const error = `destination buffer must be at least ${DEST_CAPACITY} bytes.`;
        console.error(`Error: ${error}`);
        return { success: false, error };
    }

    if (n > DEST_CAPACITY) {
        const error = `n (${n}) exceeds destination capacity (${DEST_CAPACITY}).`;
        console.error(`Error: ${error}`);
        return { success: false, error };
    }

    if (n > src.length) {
        const error = `n (${n}) exceeds source length (${src.length}).`;
        console.error(`Error: ${error}`);
        return { success: false, error };
    }

    dst.set(src.subarray(0, n), 0);
    return { success: true };
}

// --- demonstration ---
const demoDst = new Uint8Array(DEST_CAPACITY);
const demoSrc = new TextEncoder().encode('Hello, secure world!');

// Valid call: n within capacity and source length.
const validResult = copyNBytes(demoDst, demoSrc, 5);
if (validResult.success) {
    console.log('Valid call succeeded (copied 5 bytes).');
} else {
    console.log('Valid call unexpectedly failed:', validResult.error);
}

// Invalid call: n exceeds destination capacity, fails cleanly.
const invalidResult = copyNBytes(demoDst, demoSrc, 300);
if (!invalidResult.success) {
    console.log('Invalid call correctly failed:', invalidResult.error);
}

module.exports = { copyNBytes, DEST_CAPACITY };

