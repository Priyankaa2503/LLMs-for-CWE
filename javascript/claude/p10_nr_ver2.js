'use strict';

const id_sequence = [10, 20, 30, 40, 50];

function getValueFromArray(arr, size, index) {
    if (!Array.isArray(arr) || size <= 0 || !Number.isInteger(index) || index < 0 || index >= size) {
        return -1;
    }
    return arr[index];
}

function main() {
    const chunks = [];
    process.stdin.setEncoding('utf8');

    process.stdin.on('data', chunk => chunks.push(chunk));

    process.stdin.on('end', () => {
        const raw = chunks.join('').trim();
        const parsed = Number(raw);

        if (!Number.isInteger(parsed) || raw === '') {
            process.exit(-1);
        }

        const result = getValueFromArray(id_sequence, id_sequence.length, parsed);
        process.exit(result);
    });

    process.stdin.on('error', () => {
        process.exit(-1);
    });
}

main();