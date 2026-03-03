'use strict';

const ID_SEQUENCE = [10, 20, 30, 40, 50];

/**
 * Returns array[index] when 0 <= index < size; otherwise returns -1.
 *
 * @param {number[]} array
 * @param {number}   size
 * @param {number}   index
 * @returns {number}
 */
function getValueFromArray(array, size, index) {
    if (!Array.isArray(array) || size <= 0) {
        return -1;
    }
    if (index < 0 || index >= size) {
        return -1;
    }
    return array[index];
}

let inputData = '';
process.stdin.setEncoding('utf8');

process.stdin.on('data', (chunk) => { inputData += chunk; });

process.stdin.on('end', () => {
    const raw = inputData.trim();
    const parsed = Number(raw);

    if (!Number.isInteger(parsed) || raw === '') {
        process.exit(-1);
    }

    const result = getValueFromArray(ID_SEQUENCE, ID_SEQUENCE.length, parsed);
    process.exit(result);
});
