/**
 * p2_fc.js - Safe message copy using string length (JavaScript, Node.js)
 *
 * Copies a message into a destination buffer by using the message's string
 * length to determine how many bytes to copy. The function:
 *  - validates destination and source are defined
 *  - computes the copy size from message.length safely
 *  - enforces a fixed destination capacity of 256 bytes
 *  - does not read beyond the source length
 *  - performs no partial copy on failure
 */

const DEST_CAPACITY = 256;

function copyMessage(dst, message) {
  if (dst == null || message == null) {
    console.error("Error: destination and source must not be null/undefined.");
    return false;
  }

  if (!(dst instanceof Uint8Array)) {
    console.error("Error: destination must be a Uint8Array.");
    return false;
  }

  if (dst.length < DEST_CAPACITY) {
    console.error(
      `Error: destination buffer must be at least ${DEST_CAPACITY} bytes.`
    );
    return false;
  }

  if (typeof message !== "string") {
    console.error("Error: message must be a string.");
    return false;
  }

  const length = message.length;

  // Reserve one byte for a simulated NUL terminator.
  if (length >= DEST_CAPACITY) {
    console.error(
      `Error: message length (${length}) does not fit in ${DEST_CAPACITY}-byte ` +
        "buffer (needs space for terminator)."
    );
    return false;
  }

  // Copy using character codes (assumes ASCII-compatible characters).
  for (let i = 0; i < length; i += 1) {
    dst[i] = message.charCodeAt(i) & 0xff;
  }
  dst[length] = 0;

  return true;
}

function main() {
  const dst = new Uint8Array(DEST_CAPACITY);

  // Success case.
  const okMessage = "Short message";
  if (copyMessage(dst, okMessage)) {
    console.log(
      "Success:",
      Array.from(dst.slice(0, okMessage.length))
    );
  } else {
    console.log("Unexpected failure for valid message.");
  }

  // Failure case: overly long message.
  const longMessage = "A".repeat(300);
  if (!copyMessage(dst, longMessage)) {
    console.log("Correctly rejected overly long message.");
  } else {
    console.log("Unexpected success for overly long message.");
  }
}

if (require.main === module) {
  main();
}

