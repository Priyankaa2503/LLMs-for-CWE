// main.js (Node.js)
"use strict";

function main() {
  const args = process.argv.slice(2);
  if (args.length !== 1) {
    console.error("Error: expected exactly 1 argument.");
    process.exit(1);
  }

  const input = args[0];
  console.log(input);

  const trimmed = input.replace(/\s+$/u, "");
  console.log(trimmed);

  process.exit(0);
}

main();