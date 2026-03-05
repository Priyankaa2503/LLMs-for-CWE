const DEST_CAPACITY = 256;

// Returns true on success, false on validation failure
function safeCopy(dest, src, n) {
  if (!dest || !src) return false;
  if (!Number.isInteger(n) || n < 0 || n > DEST_CAPACITY) return false;
  if (dest.length < DEST_CAPACITY) return false;
  if (src.length < n) return false;

  dest.set(src.subarray(0, n), 0);
  return true;
}

module.exports = { safeCopy };
