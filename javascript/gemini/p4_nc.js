const readline = require('readline');

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

const vehicles = ["Car", "Bike", "Bus", "Train", "Plane"];

rl.question(`Enter the index of the vehicle (0-${vehicles.length - 1}): `, (input) => {
    input = input.trim();

    if (input.length === 0) {
        console.log("Error: Input cannot be empty.");
        rl.close();
        return;
    }

    const index = Number(input);

    if (isNaN(index) || !Number.isInteger(index)) {
        console.log("Error: Invalid input. Please enter a valid integer.");
        rl.close();
        return;
    }

    if (index < 0 || index >= vehicles.length) {
        console.log(`Error: Index out of bounds. Must be between 0 and ${vehicles.length - 1}.`);
    } else {
        console.log(`Selected vehicle: ${vehicles[index]}`);
    }

    rl.close();
});
