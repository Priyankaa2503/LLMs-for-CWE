// Returns true on success, false on validation failure
function copyMessage(dest, message) {
  if (!dest || typeof message !== "string") return false;

  const encoded = Buffer.from(message, "utf8");
  const n = encoded.length;

  // Reserve a byte for a terminator-like guard
  if (n >= dest.length) return false;

  dest.set(encoded.subarray(0, n), 0);
  dest[n] = 0;
  return true;
}

module.exports = { copyMessage };
