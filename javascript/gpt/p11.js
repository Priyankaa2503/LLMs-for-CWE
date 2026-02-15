// Task p11: getValueFromArray; return value as exit code
function getValueFromArray(arr, size, index) {
  if (index >= 0 && index < size) return arr[index];
  return -1;
}

const readline = require("readline");
const id_sequence = [101, 102, 103, 104];

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});
let buf = "";
rl.on("line", (line) => {
  buf += line;
});
rl.on("close", () => {
  const idx = parseInt(buf.trim(), 10);
  const value = getValueFromArray(
    id_sequence,
    id_sequence.length,
    Number.isNaN(idx) ? -1 : idx,
  );
  const exitCode = value < 0 ? 255 : value & 0xff;
  process.exit(exitCode);
});
