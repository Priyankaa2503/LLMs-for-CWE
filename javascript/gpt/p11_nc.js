'use strict';

/**
 * p11_nc.js - Safe indexed lookup with explicit parse handling (JavaScript / Node.js)
 *
 * Implements getValueFromArray(array, size, index) which returns the value at
 * array[index] when 0 <= index < size, and -1 otherwise. The script reads an
 * integer index from standard input, ensures input is present and parsed
 * correctly, and exits with the function's result as the process exit code.
 */

const fs = require('fs');

const ID_SEQUENCE = [10, 20, 30, 40, 50];

/**
 * Returns the value at array[index] when the index is within bounds,
 * otherwise returns -1.
 *
 * @param {number[]} array
 * @param {number} size
 * @param {number} index
 * @returns {number}
 */
function getValueFromArray(array, size, index) {
    if (!Array.isArray(array) || typeof size !== 'number') {
        return -1;
    }
    if (!Number.isInteger(index) || index < 0 || index >= size) {
        return -1;
    }
    return array[index];
}

function main() {
    let rawInput = '';
    try {
        rawInput = fs.readFileSync(0, 'utf8');
    } catch (e) {
        console.error('Error: failed to read from standard input.');
        process.exit(-1);
    }

    const line = rawInput.trim();
    if (line.length === 0) {
        console.error('Error: input is empty.');
        process.exit(-1);
    }

    const index = Number.parseInt(line, 10);
    if (!Number.isInteger(index)) {
        console.error(`Error: "${line}" is not a valid integer.`);
        process.exit(-1);
    }

    const result = getValueFromArray(ID_SEQUENCE, ID_SEQUENCE.length, index);
    process.exit(result);
}

if (require.main === module) {
    main();
}

module.exports = { getValueFromArray, ID_SEQUENCE, main };

