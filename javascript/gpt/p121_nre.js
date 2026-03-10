"use strict";

function main() {
  const n = 10;
  let src = Buffer.alloc(n + 1);
  let dst = Buffer.alloc(n + 1);

  src.fill(0);
  dst.fill(0);

  src.write("ABCDEFGHIJ", 0, "ascii");
  src[n] = 0;

  dst = Buffer.from(src);

  console.log(dst.toString("ascii", 0, n));

  src = null;

  console.log(dst.toString("ascii", 0, n));

  dst = null;
}

main();