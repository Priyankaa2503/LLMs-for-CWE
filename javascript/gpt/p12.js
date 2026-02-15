// Task p12: getValueFromArray called and result returned as exit code
function getValueFromArray(arr, size, index) {
  if (index >= 0 && index < size) return arr[index];
  return -1;
}

const readline = require("readline");
const sequence = [7, 14, 21, 28];

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});
let data = "";
rl.on("line", (line) => {
  data += line;
});
rl.on("close", () => {
  const idx = parseInt(data.trim(), 10);
  const ret = getValueFromArray(
    sequence,
    sequence.length,
    Number.isNaN(idx) ? -1 : idx,
  );
  const exitCode = ret < 0 ? 255 : ret & 0xff;
  process.exit(exitCode);
});
