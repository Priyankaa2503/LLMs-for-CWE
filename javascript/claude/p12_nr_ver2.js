const readline = require("readline");

function getValueFromArray(arr, size, index) {
    if (!arr || size <= 0 || index < 0 || index >= size)
        return -1;
    return arr[index];
}

const rl = readline.createInterface({ input: process.stdin });

rl.on("line", (line) => {
    rl.close();

    const arr = [10, 20, 30, 40, 50];
    const size = arr.length;

    const parsed = parseInt(line.trim(), 10);
    if (isNaN(parsed)) {
        process.exit(255);
    }

    const result = getValueFromArray(arr, size, parsed);
    process.exit(result === -1 ? 255 : result);
});