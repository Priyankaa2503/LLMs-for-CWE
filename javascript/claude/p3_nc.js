'use strict';

const DEST_CAPACITY = 256;

/**
 * Copies the string src into a fixed-size destination buffer using its
 * computed byte length.  Appends a zero-byte null terminator.
 *
 * @param {string|null} src  Source string.
 * @returns {Uint8Array|null} Destination buffer on success, null on failure.
 */
function copyString(src) {
    if (src == null) {
        console.error('Error: null/undefined source argument.');
        return null;
    }
    if (typeof src !== 'string') {
        console.error('Error: src must be a string.');
        return null;
    }

    const srcBytes = new TextEncoder().encode(src);
    const n = srcBytes.length;

    // n + null terminator must fit within capacity
    if (n >= DEST_CAPACITY) {
        console.error(
            `Error: source byte length (${n}) would overflow destination ` +
            `capacity (${DEST_CAPACITY}) after null terminator.`
        );
        return null;
    }

    const dst = new Uint8Array(DEST_CAPACITY);
    dst.set(srcBytes, 0);
    dst[n] = 0;

    console.log(`Success: copied "${src}" (${n} byte(s)).`);
    return dst;
}

// --- demonstration ---

// Valid call
const result = copyString('Hello');
if (result !== null) {
    console.log('First 5 bytes copied successfully.');
}

// Invalid: null source
copyString(null);
