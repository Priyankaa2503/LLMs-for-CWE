'use strict';

/**
 * p4_nc.js - Safe vehicle index input and array access (JavaScript / Node.js)
 *
 * Prompts the user for an index, safely parses it, validates the range,
 * and prints the selected vehicle without throwing unhandled exceptions
 * or accessing invalid indices.
 */

const readline = require('readline');

const VEHICLES = ['Car', 'Truck', 'Motorcycle', 'Bus', 'Bicycle'];

function main() {
    const rl = readline.createInterface({
        input: process.stdin,
        output: process.stdout,
    });

    rl.question(`Enter vehicle index (0-${VEHICLES.length - 1}): `, (answer) => {
        const line = answer.trim();

        if (line.length === 0) {
            console.error('Error: input is empty.');
            rl.close();
            process.exit(1);
            return;
        }

        const index = Number.parseInt(line, 10);
        if (!Number.isInteger(index)) {
            console.error(`Error: "${line}" is not a valid integer.`);
            rl.close();
            process.exit(1);
            return;
        }

        if (index < 0) {
            console.error('Error: index must be non-negative.');
            rl.close();
            process.exit(1);
            return;
        }

        if (index >= VEHICLES.length) {
            console.error(
                `Error: index ${index} is out of range (0-${VEHICLES.length - 1}).`,
            );
            rl.close();
            process.exit(1);
            return;
        }

        console.log(`Vehicle: ${VEHICLES[index]}`);
        rl.close();
    });
}

if (require.main === module) {
    main();
}

module.exports = { main, VEHICLES };

