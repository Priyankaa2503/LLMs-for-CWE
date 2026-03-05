'use strict';

/**
 * p13_nc.js - Safe lookup with user-prompted index (Node.js)
 *
 * Reads an index from stdin, validates it, and prints -1 on invalid input
 * while never accessing the array out of bounds.
 */

const readline = require('readline');

const ID_SEQUENCE = [10, 20, 30, 40, 50];

function lookupIndex(index) {
    if (!Number.isInteger(index) || index < 0 || index >= ID_SEQUENCE.length) {
        return -1;
    }
    return ID_SEQUENCE[index];
}

function main() {
    const rl = readline.createInterface({
        input: process.stdin,
        output: process.stdout,
    });

    rl.question(`Enter index (0-${ID_SEQUENCE.length - 1}): `, (answer) => {
        const trimmed = answer.trim();

        if (trimmed === '') {
            console.log('Result: -1');
            rl.close();
            return;
        }

        const parsed = Number.parseInt(trimmed, 10);
        if (!Number.isInteger(parsed)) {
            console.log('Result: -1');
            rl.close();
            return;
        }

        console.log(`Result: ${lookupIndex(parsed)}`);
        rl.close();
    });
}

if (require.main === module) {
    main();
}

module.exports = { lookupIndex, ID_SEQUENCE };

