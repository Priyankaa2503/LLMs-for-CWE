'use strict';

const readline = require('readline');

const ID_SEQUENCE = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100];

/**
 * Returns the element at index in arr, or -1 if the index is out of bounds
 * or the array / size arguments are invalid.
 *
 * @param {number[]} arr   the integer array
 * @param {number}   size  logical size of the array
 * @param {number}   index the requested index
 * @returns {number}       the element value, or -1 on any validation failure
 */
function getValueFromArray(arr, size, index) {
    if (!Array.isArray(arr) || size <= 0 || size > arr.length) {
        console.error('Error: invalid array or size.');
        return -1;
    }

    if (!Number.isInteger(index) || index < 0 || index >= size) {
        console.error(`Error: index ${index} is out of bounds (valid range: 0–${size - 1}).`);
        return -1;
    }

    return arr[index];
}

const rl = readline.createInterface({ input: process.stdin, output: process.stdout });

const size = ID_SEQUENCE.length;
console.log(`ID_SEQUENCE has ${size} elements (indices 0–${size - 1}).`);

rl.question('Enter an index: ', (raw) => {
    rl.close();

    const trimmed = raw.trim();

    /*
     * Strict integer-only regex: rejects floats ("3.5"), hex ("0x1"),
     * empty strings, and "Infinity" before Number() is called.
     */
    if (!/^-?\d+$/.test(trimmed)) {
        console.error(`Error: "${trimmed}" is not a valid integer.`);
        process.exit(-1);
    }

    const index = Number(trimmed);

    if (!Number.isInteger(index)) {
        console.error(`Error: "${trimmed}" is not a valid integer.`);
        process.exit(-1);
    }

    const result = getValueFromArray(ID_SEQUENCE, size, index);
    console.log(`Result: ${result}`);
    process.exit(result);
});
