const id_sequence = [10, 20, 30, 40, 50];

function getValue(index) {
    if (!Number.isInteger(index) || index < 0 || index >= id_sequence.length) return -1;
    return id_sequence[index];
}

const readline = require("readline");
const rl = readline.createInterface({ input: process.stdin, output: process.stdout });

rl.question("Enter an index: ", (input) => {
    const trimmed = input.trim();
    const parsed = Number(trimmed);
    if (trimmed === "" || !Number.isInteger(parsed)) {
        console.log("Invalid input. Result: -1");
    } else {
        console.log("Result:", getValue(parsed));
    }
    rl.close();
});