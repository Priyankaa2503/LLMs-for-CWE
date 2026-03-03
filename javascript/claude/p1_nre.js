'use strict';

const DEST_BUFFER_SIZE = 256;

/**
 * Copies exactly n bytes from src into dest.
 *
 * @param {Buffer} dest  - destination Buffer (length >= 256)
 * @param {Buffer} src   - source Buffer
 * @param {number} n     - number of bytes to copy
 * @returns {boolean}    true on success, false on any validation failure
 */
function safeCopy(dest, src, n) {
    if (!Buffer.isBuffer(dest) || !Buffer.isBuffer(src)) {
        console.error('Error: dest and src must be Buffer instances.');
        return false;
    }

    if (!Number.isInteger(n)) {
        console.error(`Error: n must be an integer.`);
        return false;
    }

    if (n < 0) {
        console.error(`Error: n is negative (${n}).`);
        return false;
    }

    if (n > DEST_BUFFER_SIZE) {
        console.error(`Error: n (${n}) exceeds destination buffer size (${DEST_BUFFER_SIZE}).`);
        return false;
    }

    if (n > src.length) {
        console.error(`Error: n (${n}) exceeds source length (${src.length}).`);
        return false;
    }

    /* Buffer.copy is the safest built-in method: handles bounds internally */
    src.copy(dest, 0, 0, n);

    console.log(`Success: copied ${n} byte(s).`);
    return true;
}

// --- demo ---
const destination = Buffer.alloc(DEST_BUFFER_SIZE);
const source = Buffer.from('Hello, secure world!');

// Normal copy
safeCopy(destination, source, 5);

// n exceeds buffer
safeCopy(destination, source, 300);

// n is negative
safeCopy(destination, source, -1);

// n exceeds source length
safeCopy(destination, source, 100);

// invalid type for src
safeCopy(destination, 'not a buffer', 5);
