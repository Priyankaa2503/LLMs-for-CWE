'use strict';

const DEST_BUFFER_SIZE = 256;
const MESSAGE = 'Hello';

/**
 * Copies the UTF-8 bytes of the literal "Hello" into dest.
 *
 * n is derived from Buffer.byteLength(MESSAGE, 'utf8') = 5.
 *
 * @param {Buffer} dest - destination Buffer (length >= DEST_BUFFER_SIZE)
 * @returns {boolean}   true on success, false on any validation failure
 */
function copyHello(dest) {
    if (!Buffer.isBuffer(dest)) {
        console.error('Error: dest must be a Buffer instance.');
        return false;
    }

    /* Buffer.byteLength correctly accounts for multi-byte UTF-8 characters */
    const n = Buffer.byteLength(MESSAGE, 'utf8');   /* n = 5 */

    if (n > DEST_BUFFER_SIZE) {
        console.error(`Error: source byte length (${n}) exceeds destination capacity (${DEST_BUFFER_SIZE}).`);
        return false;
    }

    /* Zero-fill then write exactly n bytes using the bounds-checked Buffer API */
    dest.fill(0);
    dest.write(MESSAGE, 0, n, 'utf8');

    console.log(`Success: copied ${n} byte(s) → ${JSON.stringify(dest.toString('utf8', 0, n))}`);
    return true;
}

// --- demo ---
const destination = Buffer.alloc(DEST_BUFFER_SIZE);

// Normal copy
copyHello(destination);

// Invalid dest type
copyHello(null);
copyHello('not a buffer');
