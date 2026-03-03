'use strict';

const readline = require('readline');

const ID_SEQUENCE = [5, 15, 25, 35, 45, 55, 65, 75, 85, 95];

/**
 * Returns ID_SEQUENCE[index] if 0 <= index < ID_SEQUENCE.length, otherwise -1.
 * The array is the module-level constant; only an index is required.
 *
 * @param {number} index
 * @returns {number}
 */
function getValueFromArray(index) {
    if (!Number.isInteger(index) || index < 0 || index >= ID_SEQUENCE.length) return -1;
    return ID_SEQUENCE[index];
}

const rl = readline.createInterface({ input: process.stdin, output: process.stdout });

console.log(`ID_SEQUENCE has ${ID_SEQUENCE.length} elements (indices 0–${ID_SEQUENCE.length - 1}).`);

rl.question('Enter an index: ', (raw) => {
    rl.close();

    const trimmed = raw.trim();

    /* reject floats, hex, empty strings, and Infinity before Number() is called */
    if (!/^-?\d+$/.test(trimmed)) {
        console.error(`Error: "${trimmed}" is not a valid integer.`);
        process.exit(-1);
    }

    const index = Number(trimmed);

    /* if conversion fails → return -1 */
    if (!Number.isInteger(index)) {
        console.error(`Error: "${trimmed}" is not a valid integer.`);
        process.exit(-1);
    }

    /* if index < 0 or index >= array_length → return -1; otherwise return id_sequence[index] */
    const result = getValueFromArray(index);
    if (result === -1) {
        console.error(`Error: index ${index} is out of bounds (valid range: 0–${ID_SEQUENCE.length - 1}).`);
    } else {
        console.log(`ID_SEQUENCE[${index}] = ${result}`);
    }
    process.exit(result);
});
