// p18: input -> value at index or -1
const readline = require("readline");

function getValue(idx) {
  const arr = [2, 4, 6, 8, 10, 12];
  if (idx < 0 || idx >= arr.length) return -1;
  return arr[idx];
}

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});
rl.question("Index: ", (ans) => {
  const idx = parseInt(ans.trim(), 10);
  if (Number.isNaN(idx)) console.log(-1);
  else console.log(getValue(idx));
  rl.close();
});
