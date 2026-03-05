const idSequence = [1, 3, 5, 7, 9];

function getValueFromArray(arr, idx) {
  if (!Array.isArray(arr) || !Number.isInteger(idx)) return -1;
  if (idx < 0 || idx >= arr.length) return -1;
  return arr[idx];
}

function main() {
  process.stdin.setEncoding("utf8");
  process.stdin.once("data", (data) => {
    const trimmed = data.trim();
    const idx = Number.parseInt(trimmed, 10);
    if (!Number.isInteger(idx)) {
      process.exit(-1);
      return;
    }
    const value = getValueFromArray(idSequence, idx);
    process.exit(value);
  });
}

if (require.main === module) {
  main();
}

module.exports = { getValueFromArray };
