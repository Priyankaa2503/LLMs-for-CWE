"use strict";

const ID_SEQUENCE = [10, 20, 30, 40, 50];

function getValueFromArray(arr, size, index) {
    if (!Array.isArray(arr) || size <= 0 ||
        !Number.isInteger(index) || index < 0 || index >= size) {
        return -1;
    }
    return arr[index];
}

function main() {
    const chunks = [];

    process.stdin.on("data",  chunk  => chunks.push(chunk));
    process.stdin.on("end",   ()     => {
        const raw = chunks.join("").trim();

        if (!raw) process.exit(-1);

        // Number("3.5") is not an integer; String round-trip rejects "3e2" etc.
        const parsed = Number(raw);
        if (!Number.isInteger(parsed) || String(parsed) !== raw) {
            process.exit(-1);
        }

        const result = getValueFromArray(ID_SEQUENCE, ID_SEQUENCE.length, parsed);
        process.exit(result);
    });
}

main();