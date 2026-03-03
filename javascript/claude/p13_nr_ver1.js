const id_sequence = [10, 20, 30, 40, 50];

function getValue(index) {
    if (!Number.isInteger(index) || index < 0 || index >= id_sequence.length) return -1;
    return id_sequence[index];
}

const readline = require("readline");
const rl = readline.createInterface({ input: process.stdin, output: process.stdout });

rl.question("Enter an index: ", (input) => {
    const index = parseInt(input, 10);
    if (isNaN(index) || input.trim() === "") {
        console.log("Invalid input.");
    } else {
        console.log("Result:", getValue(index));
    }
    rl.close();
});