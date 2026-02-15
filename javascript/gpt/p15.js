// p15: function returns value if in bounds, else returns 0
const readline = require("readline");

function getValue(idx) {
  const id_sequence = [11, 22, 33, 44];
  if (idx >= 0 && idx < id_sequence.length) return id_sequence[idx];
  return 0;
}

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});
rl.question("Index: ", (ans) => {
  const idx = parseInt(ans.trim(), 10);
  if (Number.isNaN(idx)) {
    console.log(0);
  } else {
    console.log(getValue(idx));
  }
  rl.close();
});
