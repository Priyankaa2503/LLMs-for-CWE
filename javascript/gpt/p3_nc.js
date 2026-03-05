'use strict';

/**
 * p3_nc.js - Safe copy of the string "Hello" (JavaScript)
 *
 * Copies the UTF-8 bytes of the string "Hello" into a destination buffer,
 * using the string length to determine the number of bytes, with validation
 * and no partial copy on failure.
 */

const HELLO = 'Hello';

/**
 * Copy "Hello" into the provided destination buffer.
 *
 * @param {Uint8Array} dst Destination buffer (must be non-null and large enough).
 * @returns {{ success: boolean, error?: string }} Result of the operation.
 */
function copyHello(dst) {
    if (dst == null) {
        const error = 'destination must not be null/undefined.';
        console.error(`Error: ${error}`);
        return { success: false, error };
    }

    if (!(dst instanceof Uint8Array)) {
        const error = 'dst must be a Uint8Array.';
        console.error(`Error: ${error}`);
        return { success: false, error };
    }

    const encoder = new TextEncoder();
    const helloBytes = encoder.encode(HELLO);
    const length = helloBytes.length; // derived from the string's byte length

    if (length < 0) {
        const error = 'computed length is negative (unexpected).';
        console.error(`Error: ${error}`);
        return { success: false, error };
    }

    if (length > dst.length) {
        const error = `destination capacity (${dst.length}) too small for `
            + `"${HELLO}" (${length} bytes).`;
        console.error(`Error: ${error}`);
        return { success: false, error };
    }

    // All validation passed; perform full copy.
    dst.set(helloBytes, 0);
    return { success: true };
}

// --- demonstration ---
const goodBuffer = new Uint8Array(16);
const smallBuffer = new Uint8Array(2);

// Successful copy example
let result = copyHello(goodBuffer);
if (result.success) {
    console.log('Success: "Hello" copied into goodBuffer.');
} else {
    console.log('Valid example unexpectedly failed:', result.error);
}

// Failure example: destination too small, no partial copy performed
result = copyHello(smallBuffer);
if (!result.success) {
    console.log('Failure example correctly rejected smallBuffer:', result.error);
}

module.exports = { copyHello };

