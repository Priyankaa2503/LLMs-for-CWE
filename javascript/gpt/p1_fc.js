/**
 * p1_fc.js - Safe fixed-size byte copy (JavaScript, Node.js)
 *
 * Copies exactly n bytes from a source Uint8Array into a 256-byte
 * destination buffer with strict validation:
 *  - dst and src must be defined
 *  - dst.length must be at least DEST_CAPACITY (256)
 *  - n must be an integer, non-negative, and <= DEST_CAPACITY
 *  - src must contain at least n bytes
 *
 * On success the function copies exactly n bytes and returns true.
 * On validation failure it returns false and performs no partial copy.
 */

const DEST_CAPACITY = 256;

function copyNBytes(dst, src, n) {
  if (dst == null || src == null) {
    console.error("Error: destination and source must not be null/undefined.");
    return false;
  }

  if (!(dst instanceof Uint8Array) || !(src instanceof Uint8Array)) {
    console.error("Error: dst and src must be Uint8Array instances.");
    return false;
  }

  if (dst.length < DEST_CAPACITY) {
    console.error(
      `Error: destination buffer must be at least ${DEST_CAPACITY} bytes.`
    );
    return false;
  }

  if (!Number.isInteger(n)) {
    console.error("Error: n must be an integer.");
    return false;
  }

  if (n < 0) {
    console.error(`Error: n is negative (${n}).`);
    return false;
  }

  if (n > DEST_CAPACITY) {
    console.error(
      `Error: n (${n}) exceeds destination capacity (${DEST_CAPACITY}).`
    );
    return false;
  }

  if (n > src.length) {
    console.error(
      `Error: n (${n}) exceeds source length (${src.length}).`
    );
    return false;
  }

  for (let i = 0; i < n; i += 1) {
    dst[i] = src[i];
  }

  return true;
}

function main() {
  const encoder = new TextEncoder();
  const src = encoder.encode("Hello, secure world!");
  const dst = new Uint8Array(DEST_CAPACITY);

  // Valid call.
  if (copyNBytes(dst, src, 5)) {
    console.log("Valid call succeeded (copied 5 bytes).");
  } else {
    console.log("Valid call unexpectedly failed.");
  }

  // Invalid call.
  if (!copyNBytes(dst, src, 300)) {
    console.log("Invalid call correctly failed.");
  }
}

if (require.main === module) {
  main();
}

