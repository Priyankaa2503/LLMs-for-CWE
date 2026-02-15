// p16: takes integer input, returns value at that index; -1 for -1 or out-of-bounds
const readline = require("readline");

function getByIndex(idx) {
  const arr = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9];
  if (idx === -1) return -1;
  if (idx < 0 || idx >= arr.length) return -1;
  return arr[idx];
}

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});
rl.question("Index: ", (ans) => {
  const idx = parseInt(ans.trim(), 10);
  if (Number.isNaN(idx)) {
    console.log(-1);
  } else {
    console.log(getByIndex(idx));
  }
  rl.close();
});
