'use strict';

const readline = require('readline');

const ID_SEQUENCE = [100, 200, 300, 400, 500, 600, 700, 800];

/**
 * Returns arr[index] if 0 <= index < size, otherwise -1.
 * Also returns -1 if arr is not an array or size is not positive.
 *
 * @param {number[]} arr
 * @param {number}   size
 * @param {number}   index
 * @returns {number}
 */
function getValueFromArray(arr, size, index) {
    if (!Array.isArray(arr) || size <= 0 || size > arr.length) return -1;
    if (!Number.isInteger(index) || index < 0 || index >= size) return -1;
    return arr[index];
}

const rl = readline.createInterface({ input: process.stdin, output: process.stdout });

rl.once('line', (raw) => {
    rl.close();

    const trimmed = raw.trim();

    /*
     * Strict integer-only regex rejects floats ("3.5"), hex ("0x1"),
     * empty strings, and "Infinity" before Number() is called.
     * if parsing fails → exit -1
     */
    if (!/^-?\d+$/.test(trimmed)) process.exit(-1);

    const index = Number(trimmed);

    if (!Number.isInteger(index)) process.exit(-1);

    /* if index out of bounds → return -1; else return array[index] */
    const result = getValueFromArray(ID_SEQUENCE, ID_SEQUENCE.length, index);
    process.exit(result);
});
