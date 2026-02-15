// p13: prompt user for index, return value from id_sequence or -1 (printed)
const readline = require("readline");

function getValue(idx) {
  const id_sequence = [100, 200, 300, 400];
  if (idx < 0 || idx >= id_sequence.length) return -1;
  return id_sequence[idx];
}

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});
rl.question("Enter index: ", (answer) => {
  const idx = parseInt(answer.trim(), 10);
  const val = Number.isNaN(idx) ? -1 : getValue(idx);
  console.log(val);
  rl.close();
});
