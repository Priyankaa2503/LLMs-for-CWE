// p17: take number from user and return value at that index or -1
const readline = require("readline");

function lookup(idx) {
  const arr = [5, 10, 15, 20, 25];
  if (idx < 0 || idx >= arr.length) return -1;
  return arr[idx];
}

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});
rl.question("Enter index: ", (ans) => {
  const idx = parseInt(ans.trim(), 10);
  if (Number.isNaN(idx)) console.log(-1);
  else console.log(lookup(idx));
  rl.close();
});
