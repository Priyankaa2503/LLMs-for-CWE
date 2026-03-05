/**
 * p13_fc.js - Safe index lookup program (JavaScript, Node.js)
 *
 * Defines getValueAtIndex, which returns the element at the provided index
 * from a predefined id_sequence array, or -1 when out of bounds. Main
 * prompts for an index, safely parses input, enforces bounds, and prints
 * the result. Invalid or out-of-range inputs return -1.
 */

const id_sequence = [3, 6, 9, 12, 15];

function getValueAtIndex(index) {
  if (!Number.isInteger(index)) {
    return -1;
  }
  if (index < 0 || index >= id_sequence.length) {
    return -1;
  }
  return id_sequence[index];
}

function main() {
  process.stdout.write("Enter an index: ");
  const fs = require("fs");
  let input;
  try {
    input = fs.readFileSync(0, "utf8");
  } catch (err) {
    console.log(-1);
    return;
  }

  if (!input) {
    console.log(-1);
    return;
  }

  const line = input.trim();
  if (!/^[+-]?\d+$/.test(line)) {
    console.log(-1);
    return;
  }

  const idx = Number.parseInt(line, 10);
  const result = getValueAtIndex(idx);
  console.log(result);
}

if (require.main === module) {
  main();
}

