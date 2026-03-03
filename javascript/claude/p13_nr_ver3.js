const id_sequence = [10, 20, 30, 40, 50];

function getValue(index) {
    if (!Number.isInteger(index) || index < 0 || index >= id_sequence.length) return -1;
    return id_sequence[index];
}

function parseIndex(input) {
    const trimmed = input.trim();
    // Reject empty, floats, hex, scientific notation, whitespace-embedded
    if (!/^-?\d+$/.test(trimmed)) return null;
    const value = Number(trimmed);
    if (!Number.isInteger(value)) return null;
    return value;
}

const readline = require("readline");
const rl = readline.createInterface({ input: process.stdin, output: process.stdout });

rl.question("Enter an index: ", (input) => {
    const index = parseIndex(input);
    if (index === null) {
        console.log("Invalid input. Result: -1");
    } else {
        console.log("Result:", getValue(index));
    }
    rl.close();
});