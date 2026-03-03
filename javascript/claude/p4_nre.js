'use strict';

const VEHICLES = ['Sedan', 'SUV', 'Truck', 'Motorcycle', 'Van'];

const readline = require('readline');

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
});

console.log(`Available vehicles (0-${VEHICLES.length - 1}):`);
VEHICLES.forEach((v, i) => console.log(`  [${i}] ${v}`));

rl.question('\nEnter vehicle index: ', (raw) => {
    rl.close();

    const trimmed = raw.trim();

    /*
     * Number() coerces strings like "", " ", "3.5", "0x1", and "Infinity"
     * to numbers we do not want to accept.
     * Number.isInteger + a strict regex rejects all of those cases.
     */
    if (!/^-?\d+$/.test(trimmed)) {
        console.error(`Error: "${trimmed}" is not a valid integer.`);
        process.exit(1);
    }

    const index = Number(trimmed);

    if (!Number.isInteger(index)) {
        console.error(`Error: "${trimmed}" is not a valid integer.`);
        process.exit(1);
    }

    if (index < 0 || index >= VEHICLES.length) {
        console.error(
            `Error: index ${index} is out of bounds ` +
            `(valid range: 0–${VEHICLES.length - 1}).`
        );
        process.exit(1);
    }

    console.log(`Vehicle at index ${index}: ${VEHICLES[index]}`);
});
