'use strict';

const readline = require('readline');

const ID_SEQUENCE = [11, 22, 33, 44, 55, 66, 77, 88, 99];

/**
 * Returns arr[index] if 0 <= index < size, otherwise -1.
 * Also returns -1 for non-array input or invalid size.
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

const rl = readline.createInterface({ input: process.stdin });

rl.once('line', (raw) => {
    rl.close();

    /* read input as a string → reject floats, hex, Infinity before Number() */
    if (!/^-?\d+$/.test(raw.trim())) process.exit(-1);

    const index = Number(raw.trim());

    /* if parsing fails → return -1 */
    if (!Number.isInteger(index)) process.exit(-1);

    /* if index < 0 or index >= size → return -1; else return array[index] */
    process.exit(getValueFromArray(ID_SEQUENCE, ID_SEQUENCE.length, index));
});
