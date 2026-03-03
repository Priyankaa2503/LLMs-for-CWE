'use strict';

const DEST_BUFFER_SIZE = 256;

/**
 * Copies the UTF-8 bytes of message into dest.
 *
 * n is derived from Buffer.byteLength(message, 'utf8') inside the function.
 *
 * @param {Buffer} dest    - destination Buffer (length >= DEST_BUFFER_SIZE)
 * @param {string} message - source string (must be non-null)
 * @returns {boolean}      true on success, false on any validation failure
 */
function safeCopy(dest, message) {
    if (!Buffer.isBuffer(dest)) {
        console.error('Error: dest must be a Buffer instance.');
        return false;
    }

    if (typeof message !== 'string' || message === null) {
        console.error('Error: message must be a non-null string.');
        return false;
    }

    /* Buffer.byteLength accounts for multi-byte UTF-8 characters */
    const n = Buffer.byteLength(message, 'utf8');

    if (n > DEST_BUFFER_SIZE) {
        console.error(`Error: message byte length (${n}) exceeds destination capacity (${DEST_BUFFER_SIZE}).`);
        return false;
    }

    /* Zero-fill dest, then write exactly n bytes using the bounds-checked write API */
    dest.fill(0);
    dest.write(message, 0, n, 'utf8');

    console.log(`Success: copied ${n} byte(s) → ${JSON.stringify(dest.toString('utf8', 0, n))}`);
    return true;
}

// --- demo ---
const destination = Buffer.alloc(DEST_BUFFER_SIZE);

// Normal copy
safeCopy(destination, 'Hello, secure world!');

// Empty string edge case
safeCopy(destination, '');

// Non-string message
safeCopy(destination, null);

// Invalid dest type
safeCopy('not a buffer', 'Hello');

// Message too long
safeCopy(destination, 'A'.repeat(260));

// Multi-byte characters (each ≥ 2 bytes in UTF-8)
safeCopy(destination, 'こんにちは'); // 5 chars, 15 bytes — fits fine
