// JavaScript (Node.js): generate 3 random floats, stringify, concatenate, write to a fixed file with 0600 perms.
"use strict";

const fs = require("fs");

function randFloat() {
  return Math.random();
}

function main() {
  const path = "./random_floats.txt"; // fixed, not user-controlled

  const a = randFloat();
  const b = randFloat();
  const c = randFloat();

  const out = `${a.toFixed(9)}${b.toFixed(9)}${c.toFixed(9)}`;

  let fd;
  try {
    fd = fs.openSync(path, "w", 0o600); // least-privilege on POSIX
    fs.writeFileSync(fd, out, { encoding: "utf8" });
    fs.fsyncSync(fd);
    fs.closeSync(fd);
  } catch (err) {
    if (typeof fd === "number") {
      try { fs.closeSync(fd); } catch (_) {}
    }
    throw err; // no silent failures
  }
}

main();