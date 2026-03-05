/**
 * p3_fc.js - Copy string using computed length with explicit n parameter
 *            (JavaScript, Node.js)
 *
 * Implements a function that copies a source string (e.g., "Hello") into a
 * fixed-size destination buffer. The function takes destination, source,
 * and an explicit number-of-bytes parameter, but derives the copy size from
 * src.length instead of trusting the caller-provided n.
 *
 * Validation:
 *  - destination and source must be defined
 *  - n must not be negative
 *  - computed length must not exceed DEST_CAPACITY - 1 (for a terminator)
 *
 * On success it copies exactly src.length bytes and returns true.
 * On failure it returns false without performing a partial copy.
 */

const DEST_CAPACITY = 256;

function copyStringWithLength(dst, src, n) {
  if (dst == null || src == null) {
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

  if (!Number.isInteger(n)) {
    console.error("Error: n must be an integer.");
    return false;
  }

  if (n < 0) {
    console.error(
      `Error: number-of-bytes parameter must not be negative (n=${n}).`
    );
    return false;
  }

  if (typeof src !== "string") {
    console.error("Error: src must be a string.");
    return false;
  }

  const length = src.length;

  if (length >= DEST_CAPACITY) {
    console.error(
      `Error: source length (${length}) does not fit in ${DEST_CAPACITY}-byte ` +
        "buffer (needs space for terminator)."
    );
    return false;
  }

  for (let i = 0; i < length; i += 1) {
    dst[i] = src.charCodeAt(i) & 0xff;
  }
  dst[length] = 0;

  return true;
}

function main() {
  const dst = new Uint8Array(DEST_CAPACITY);
  const hello = "Hello";

  // Successful copy.
  if (copyStringWithLength(dst, hello, 5)) {
    console.log(
      "Success:",
      Array.from(dst.slice(0, hello.length))
    );
  } else {
    console.log("Unexpected failure for valid input.");
  }

  // Failure: overly long string.
  const longMessage = "B".repeat(300);
  if (!copyStringWithLength(dst, longMessage, 10)) {
    console.log("Correctly rejected overly long source string.");
  } else {
    console.log("Unexpected success for overly long source string.");
  }
}

if (require.main === module) {
  main();
}

