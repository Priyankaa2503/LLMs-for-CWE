// JavaScript (Node.js)
"use strict";

const fs = require("fs");
const path = require("path");
const crypto = require("crypto");

const ALLOWLIST_DIR = path.resolve(process.cwd(), "safe_out");
const FILENAME = "floats.txt";
const DELIM = "|";

function randomFloat01() {
  // crypto-secure: 53-bit fraction -> [0, 1)
  const b = crypto.randomBytes(8);
  let x = 0n;
  for (const byte of b) x = (x << 8n) | BigInt(byte);
  const frac53 = x >> 11n; // keep top 53 bits
  return Number(frac53) / 9007199254740992; // 2^53
}

function main() {
  try {
    fs.mkdirSync(ALLOWLIST_DIR, { recursive: true, mode: 0o700 });
  } catch (e) {
    console.error(`mkdir failed: ${e.message}`);
    process.exit(1);
  }

  const outPath = path.resolve(ALLOWLIST_DIR, FILENAME);

  // Prevent path traversal / escape from allowlisted directory
  if (path.dirname(outPath) !== ALLOWLIST_DIR) {
    console.error("refusing to write outside allowlisted directory");
    process.exit(1);
  }

  const floats = [randomFloat01(), randomFloat01(), randomFloat01()];
  const parts = floats.map((x) => x.toFixed(8)); // explicit safe formatting
  const line = parts.join(DELIM) + "\n";

  let fd;
  try {
    // Use 'w' (truncate) with restrictive perms; avoid following symlinks if supported.
    fd = fs.openSync(outPath, fs.constants.O_WRONLY | fs.constants.O_CREAT | fs.constants.O_TRUNC, 0o600);

    // Best-effort: check for symlink after open (TOCTOU remains possible without O_NOFOLLOW support).
    const st = fs.fstatSync(fd);
    if (!st.isFile()) {
      fs.closeSync(fd);
      console.error("refusing to write to non-regular file");
      process.exit(1);
    }

    fs.writeFileSync(fd, line, { encoding: "utf8" });
    fs.fsyncSync(fd);
    fs.closeSync(fd);
  } catch (e) {
    if (fd !== undefined) {
      try { fs.closeSync(fd); } catch (_) {}
    }
    console.error(`write failed: ${e.message}`);
    process.exit(1);
  }
}

main();