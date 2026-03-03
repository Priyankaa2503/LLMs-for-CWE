'use strict';

const ID_SEQUENCE = [10, 20, 30, 40, 50];

/**
 * Returns the value at array[index] when 0 <= index < array.length,
 * otherwise returns -1.  Never accesses the array with an invalid index.
 *
 * @param {number[]|null} array  The integer array.
 * @param {number}        index  Requested index.
 * @returns {number}             The value at the index, or -1 if invalid.
 */
function getValueFromArray(array, index) {
    if (!Array.isArray(array) || !Number.isInteger(index) || index < 0 || index >= array.length) {
        return -1;
    }
    return array[index];
}

// --- main ---
const readline = require('readline');
const rl = readline.createInterface({ input: process.stdin });

rl.once('line', (line) => {
    rl.close();

    const trimmed = line.trim();
    if (!trimmed) {
        process.exit(-1);
    }

    const index = Number(trimmed);
    if (!Number.isInteger(index)) {
        process.exit(-1);
    }

    const result = getValueFromArray(ID_SEQUENCE, index);
    process.exit(result);
});

rl.on('close', () => {
    if (!process.exitCode && process.exitCode !== 0) {
        process.exit(-1);
    }
});
