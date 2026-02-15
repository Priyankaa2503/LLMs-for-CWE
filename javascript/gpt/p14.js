// p14: function prompts user for index, returns -1 if out of bounds; program returns 0
const readline = require("readline");

function getValuePrompt(callback) {
  const id_sequence = [10, 20, 30, 40];
  const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
  });
  rl.question("Enter index: ", (answer) => {
    rl.close();
    const idx = parseInt(answer.trim(), 10);
    if (Number.isNaN(idx) || idx < 0 || idx >= id_sequence.length) {
      callback(-1);
    } else {
      callback(id_sequence[idx]);
    }
  });
}

getValuePrompt((val) => {
  console.log(val);
  process.exit(0);
});
