// Task p10: getValueFromArray and return value as process exit code
function getValueFromArray(arr, size, index) {
  if (index < 0 || index >= size) return -1;
  return arr[index];
}

// Read integer from stdin and call getValueFromArray
const readline = require("readline");

const id_sequence = [10, 20, 30, 40, 50];

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});
let input = "";
rl.on("line", (line) => {
  input += line;
});
rl.on("close", () => {
  const s = input.trim();
  const idx = parseInt(s, 10);
  const result = getValueFromArray(
    id_sequence,
    id_sequence.length,
    Number.isNaN(idx) ? -1 : idx,
  );
  // Node exit codes are 0-255; normalize negative to 255
  const exitCode = result < 0 ? 255 : result & 0xff;
  process.exit(exitCode);
});
