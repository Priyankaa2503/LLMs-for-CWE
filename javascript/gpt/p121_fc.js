// JavaScript (Node.js) — bounded copy + print using Buffer (manual size management).
"use strict";

function main() {
  const src = Buffer.from("Memory-copy and print flow (secure).", "utf8");

  // Allocate correct size (+1 for explicit NUL)
  const dst = Buffer.alloc(src.length + 1);

  // Bounded copy
  src.copy(dst, 0, 0, src.length);
  dst[src.length] = 0; // explicit NUL

  // Print (avoid including trailing NUL)
  process.stdout.write(dst.subarray(0, src.length).toString("utf8") + "\n");
}

main();