'use strict';

const DEST_CAPACITY = 256;
const encoder = new TextEncoder();

/**
 * Copies message into dst using the message's encoded byte length.
 *
 * @param {Uint8Array} dst      Destination buffer (length >= DEST_CAPACITY).
 * @param {string}     message  Source string.
 * @returns {boolean}           true on success, false on any validation failure.
 */
function copyMessage(dst, message) {
    if (dst == null || message == null) {
        console.error('Error: null/undefined argument.');
        return false;
    }
    if (!(dst instanceof Uint8Array)) {
        console.error('Error: dst must be a Uint8Array.');
        return false;
    }
    if (typeof message !== 'string') {
        console.error('Error: message must be a string.');
        return false;
    }

    const srcBytes = encoder.encode(message);
    const copyLen = srcBytes.length;

    if (copyLen > DEST_CAPACITY) {
        console.error(`Error: message byte length (${copyLen}) exceeds destination capacity (${DEST_CAPACITY}).`);
        return false;
    }

    dst.fill(0);
    dst.set(srcBytes.subarray(0, copyLen), 0);
    console.log(`Success: copied ${copyLen} byte(s).`);
    return true;
}

// --- demonstration ---
const dst = new Uint8Array(DEST_CAPACITY);

// Success case
copyMessage(dst, 'Hello, secure world!');
console.log('dst starts with:', new TextDecoder().decode(dst.subarray(0, 20)));

// Message too long
copyMessage(dst, 'A'.repeat(DEST_CAPACITY + 1));

// null message
copyMessage(dst, null);
