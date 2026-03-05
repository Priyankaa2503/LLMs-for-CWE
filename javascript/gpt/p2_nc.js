'use strict';

/**
 * p2_nc.js - Safe message-to-buffer copy using string length (JavaScript)
 *
 * Copies bytes from a source message into a destination buffer, using the
 * encoded byte length of the message as the number of bytes to copy.
 */

const DEST_CAPACITY = 256;

/**
 * Copy bytes from msg into dst using the message's encoded length.
 *
 * @param {string|Uint8Array|null} msg Source message.
 * @param {Uint8Array} dst             Destination buffer.
 * @returns {{ success: boolean, error?: string }} Result of the operation.
 */
function copyMessageToBuffer(msg, dst) {
    if (dst == null || msg == null) {
        const error = 'destination and message must not be null/undefined.';
        console.error(`Error: ${error}`);
        return { success: false, error };
    }

    if (!(dst instanceof Uint8Array)) {
        const error = 'dst must be a Uint8Array instance.';
        console.error(`Error: ${error}`);
        return { success: false, error };
    }

    if (dst.length <= 0) {
        const error = 'destination capacity must be positive.';
        console.error(`Error: ${error}`);
        return { success: false, error };
    }

    let msgBytes;
    if (typeof msg === 'string') {
        msgBytes = new TextEncoder().encode(msg);
    } else if (msg instanceof Uint8Array) {
        msgBytes = msg;
    } else {
        const error = 'msg must be a string or Uint8Array.';
        console.error(`Error: ${error}`);
        return { success: false, error };
    }

    const copyLen = msgBytes.length; // derived from encoded byte length

    if (copyLen < 0) {
        const error = 'computed length is negative (unexpected).';
        console.error(`Error: ${error}`);
        return { success: false, error };
    }

    if (copyLen > DEST_CAPACITY || copyLen > dst.length) {
        const error = `copy length (${copyLen}) exceeds destination capacity ` +
            `(${Math.min(DEST_CAPACITY, dst.length)}).`;
        console.error(`Error: ${error}`);
        return { success: false, error };
    }

    dst.set(msgBytes.subarray(0, copyLen), 0);
    return { success: true };
}

// --- demonstration ---
const demoDst = new Uint8Array(DEST_CAPACITY);

// Successful copy example
let result = copyMessageToBuffer('Hello, secure world!', demoDst);
if (result.success) {
    console.log('Success: copied message bytes.');
} else {
    console.log('Valid example unexpectedly failed:', result.error);
}

// Failure example: destination too small for message
const smallDst = new Uint8Array(8);
result = copyMessageToBuffer('This message is too long for 8 bytes', smallDst);
if (!result.success) {
    console.log('Failure example correctly rejected oversize copy:', result.error);
}

module.exports = { copyMessageToBuffer, DEST_CAPACITY };

