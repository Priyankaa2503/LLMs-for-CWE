"use strict";
const readline = require("readline");

function getValueFromArray(arr, size, index) {
    if (!Array.isArray(arr) || size <= 0 || index < 0 || index >= size)
        return -1;
    return arr[index];
}

const rl = readline.createInterface({ input: process.stdin });

rl.once("line", (line) => {
    rl.close();

    const arr = [10, 20, 30, 40, 50];
    const size = arr.length;

    const trimmed = line.trim();
    const parsed = parseInt(trimmed, 10);

    // Reject NaN, floats ("2.9"), and strings with extra chars ("2abc")
    if (isNaN(parsed) || String(parsed) !== trimmed) {
        process.exit(255);
    }

    const result = getValueFromArray(arr, size, parsed);
    process.exit(result === -1 ? 255 : result);
});

rl.once("close", () => {
    // Triggered on EOF with no input
    process.exit(255);
});