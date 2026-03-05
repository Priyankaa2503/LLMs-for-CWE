const HELLO = Buffer.from("Hello", "utf8");

// Returns true on success, false on validation failure
function copyHello(dest) {
  if (!dest) return false;
  const n = HELLO.length;
  if (dest.length < n + 1) return false;

  dest.set(HELLO, 0);
  dest[n] = 0;
  return true;
}

module.exports = { copyHello };
