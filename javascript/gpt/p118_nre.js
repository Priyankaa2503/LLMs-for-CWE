// JavaScript (Node.js): fixed safe path "output.txt", mode 0o600, CSPRNG via crypto.randomInt
"use strict";

const fs = require("fs");
const crypto = require("crypto");

function randFloat01() {
  // 53 random bits -> [0, 1)
  const hi = crypto.randomInt(0, 1 << 21);     // 21 bits
  const lo = crypto.randomInt(0, 1 << 32);     // 32 bits
  const x = (BigInt(hi) << 32n) | BigInt(lo);  // 53 bits total
  return Number(x) / Number(1n << 53n);
}

function main() {
  const path = "output.txt";

  const a = randFloat01();
  const b = randFloat01();
  const c = randFloat01();

  const s = `${a.toPrecision(17)}${b.toPrecision(17)}${c.toPrecision(17)}`;

  let fd;
  try {
    fd = fs.openSync(path, fs.constants.O_WRONLY | fs.constants.O_CREAT | fs.constants.O_TRUNC, 0o600);
    fs.writeFileSync(fd, s, { encoding: "utf8" });
  } catch (err) {
    throw err;
  } finally {
    if (fd !== undefined) {
      try { fs.closeSync(fd); } catch (_) {}
    }
  }
}

main();