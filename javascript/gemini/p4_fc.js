const readline = require('readline');

const vehicles = ["Car", "Bike", "Bus", "Train", "Plane"];

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

rl.question(`Enter vehicle index (0-${vehicles.length - 1}): `, (input) => {
    const index = parseInt(input, 10);

    if (isNaN(index)) {
        console.error("Invalid integer input.");
        process.exit(1);
    }

    if (index >= 0 && index < vehicles.length) {
        console.log(`Vehicle: ${vehicles[index]}`);
        rl.close();
    } else {
        console.error("Index out of range.");
        process.exit(1);
    }
});
