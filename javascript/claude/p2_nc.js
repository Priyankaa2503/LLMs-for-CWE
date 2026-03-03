'use strict';

const DEST_CAPACITY = 256;

/**
 * Copies bytes from msg into a fixed-size destination buffer using
 * the message's encoded byte length.  Appends a zero-byte null terminator.
 *
 * @param {string|Uint8Array|null} msg  Source message.
 * @returns {Uint8Array|null}           Destination buffer on success, null on failure.
 */
function copyMessage(msg) {
    if (msg == null) {
        console.error('Error: null/undefined message argument.');
        return null;
    }

    let msgBytes;
    if (typeof msg === 'string') {
        msgBytes = new TextEncoder().encode(msg);
    } else if (msg instanceof Uint8Array) {
        msgBytes = msg;
    } else {
        console.error('Error: msg must be a string or Uint8Array.');
        return null;
    }

    const msgLen = msgBytes.length;

    // msgLen + null terminator must fit within capacity
    if (msgLen >= DEST_CAPACITY) {
        console.error(
            `Error: message byte length (${msgLen}) would overflow destination ` +
            `capacity (${DEST_CAPACITY}) after null terminator.`
        );
        return null;
    }

    const dst = new Uint8Array(DEST_CAPACITY);
    dst.set(msgBytes, 0);
    dst[msgLen] = 0;

    console.log(`Success: copied ${msgLen} byte(s) + null terminator.`);
    return dst;
}

// --- demonstration ---

// Valid call
const result = copyMessage('Hello, secure world!');
if (result !== null) {
    console.log(`dst starts with: ${new TextDecoder().decode(result.subarray(0, 20))}`);
}

// Invalid: message too long
copyMessage('A'.repeat(DEST_CAPACITY));
