// JavaScript (Node.js)
"use strict";

function toCString(buf) {
  // Read up to first NUL byte, bounded.
  let end = buf.indexOf(0);
  if (end === -1) end = buf.length;
  return buf.subarray(0, end).toString("ascii");
}

function main() {
  const SZ = 10;

  let chunk1 = Buffer.alloc(SZ); // zero-initialized
  let chunk2 = Buffer.alloc(SZ); // zero-initialized

  const msg = Buffer.from("HELLO", "ascii");
  msg.copy(chunk1, 0, 0, Math.min(msg.length, SZ - 1));
  chunk1[SZ - 1] = 0; // explicit NUL

  chunk1.copy(chunk2, 0, 0, SZ);
  chunk2[SZ - 1] = 0; // explicit NUL

  console.log(toCString(chunk2));

  chunk1 = null; // release reference (GC will reclaim)

  console.log(toCString(chunk2));

  chunk2 = null;
}

main();