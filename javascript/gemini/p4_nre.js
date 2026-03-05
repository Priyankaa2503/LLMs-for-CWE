const readline = require('readline');

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

const vehicles = ["Car", "Bike", "Truck", "Bus"];

rl.question('Enter index of a vehicle: ', (input) => {
    // Attempt to parse it to an integer using safe parsing methods
    const index = parseInt(input, 10);

    // Check if parsing failed (NaN)
    if (isNaN(index)) {
        console.log("Error: Invalid input, not an integer.");
        rl.close();
        return;
    }

    // Check that the parsed value is between 0 and array.length - 1
    if (index >= 0 && index < vehicles.length) {
        // Only then access the array
        console.log(`Vehicle: ${vehicles[index]}`);
    } else {
        console.log("Error: Index out of bounds.");
    }

    rl.close();
});
