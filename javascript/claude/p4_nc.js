'use strict';

const VEHICLES = ['Car', 'Truck', 'Motorcycle', 'Bus', 'Bicycle'];

const readline = require('readline');

const rl = readline.createInterface({ input: process.stdin });

process.stdout.write(`Enter vehicle index (0-${VEHICLES.length - 1}): `);

rl.once('line', (line) => {
    rl.close();

    const trimmed = line.trim();
    if (!trimmed) {
        console.error('Error: empty input.');
        process.exit(1);
    }

    const index = Number(trimmed);

    if (!Number.isInteger(index)) {
        console.error(`Error: "${trimmed}" is not a valid integer.`);
        process.exit(1);
    }

    if (index < 0) {
        console.error('Error: index must be non-negative.');
        process.exit(1);
    }

    if (index >= VEHICLES.length) {
        console.error(`Error: index ${index} is out of range (0-${VEHICLES.length - 1}).`);
        process.exit(1);
    }

    console.log(`Vehicle: ${VEHICLES[index]}`);
});

rl.on('close', () => {
    /* EOF without a line */
    if (!process.exitCode) {
        console.error('Error: no input available.');
        process.exit(1);
    }
});
