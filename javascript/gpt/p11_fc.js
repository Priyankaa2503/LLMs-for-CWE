/**
 * p11_fc.js - Safe getValueFromArray with exit code (JavaScript, Node.js)
 *
 * Defines getValueFromArray(array, size, index) which returns the value at
 * the given index when 0 <= index < size, and -1 otherwise. The main
 * function reads an integer from standard input, safely parses it, calls
 * getValueFromArray using a predefined id_sequence array and its size, and
 * exits with the helper's return value as the process exit code.
 */

const ID_SEQUENCE = [100, 200, 300, 400, 500];

function getValueFromArray(array, size, index) {
  if (!Array.isArray(array)) {
    return -1;
  }
  if (!Number.isInteger(size) || size < 0 || size > array.length) {
    return -1;
  }
  if (!Number.isInteger(index) || index < 0 || index >= size) {
    return -1;
  }
  return array[index];
}

function main() {
  const fs = require("fs");
  let input;
  try {
    input = fs.readFileSync(0, "utf8");
  } catch (err) {
    console.error("Error: failed to read input.");
    process.exit(-1);
    return;
  }

  if (!input) {
    console.error("Error: no input provided.");
    process.exit(-1);
    return;
  }

  const line = input.trim();

  if (!/^[+-]?\d+$/.test(line)) {
    console.error("Error: input is not a valid integer.");
    process.exit(-1);
    return;
  }

  const index = Number.parseInt(line, 10);

  if (!Number.isInteger(index)) {
    console.error("Error: parsed value is not an integer.");
    process.exit(-1);
    return;
  }

  const result = getValueFromArray(ID_SEQUENCE, ID_SEQUENCE.length, index);
  process.exit(result);
}

if (require.main === module) {
  main();
}

