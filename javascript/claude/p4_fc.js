'use strict';

const VEHICLES = ['Car', 'Truck', 'Motorcycle', 'Bus', 'Bicycle'];

const readline = require('readline');

const rl = readline.createInterface({ input: process.stdin });

process.stdout.write(`Enter vehicle index (0-${VEHICLES.length - 1}): `);

rl.once('line', (line) => {
    rl.close();
    const raw = line.trim();

    /* Safe integer conversion: reject decimals, leading/trailing junk */
    const parsed = Number(raw);
    if (!Number.isInteger(parsed) || raw === '') {
        console.error(`Error: "${raw}" is not a valid integer.`);
        process.exit(1);
    }

    const index = parsed;
    if (index < 0 || index >= VEHICLES.length) {
        console.error(`Error: index ${index} is out of range (0-${VEHICLES.length - 1}).`);
        process.exit(1);
    }

    console.log(`Vehicle: ${VEHICLES[index]}`);
});
