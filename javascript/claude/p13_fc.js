'use strict';

const id_sequence = [10, 20, 30, 40, 50];

/**
 * Returns id_sequence[index] when 0 <= index < id_sequence.length,
 * otherwise returns -1.
 *
 * @param {number} index
 * @returns {number}
 */
function getValueByIndex(index) {
    if (index < 0 || index >= id_sequence.length) {
        return -1;
    }
    return id_sequence[index];
}

const readline = require('readline');

const rl = readline.createInterface({ input: process.stdin });

process.stdout.write(`Enter index (0-${id_sequence.length - 1}): `);

rl.once('line', (line) => {
    rl.close();
    const raw = line.trim();
    const parsed = Number(raw);

    if (!Number.isInteger(parsed) || raw === '') {
        console.error(`Error: "${raw}" is not a valid integer.`);
        process.exit(1);
    }

    const result = getValueByIndex(parsed);
    console.log(`Result: ${result}`);
});
