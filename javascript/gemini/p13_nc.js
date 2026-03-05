const readline = require('readline');

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

const id_sequence = [10, 20, 30, 40, 50];

function getValueFromArray(array, index) {
    if (index < 0 || index >= array.length) {
        return -1;
    }
    return array[index];
}

rl.question('Enter an index: ', (input) => {
    input = input.trim();
    
    if (input.length === 0) {
        console.log("Error: Input cannot be empty.");
        process.exit(-1);
    }

    const index = Number(input);

    if (isNaN(index) || !Number.isInteger(index)) {
        console.log("Error: Invalid integer input.");
        process.exit(-1);
    }

    if (index < 0 || index >= id_sequence.length) {
        console.log("Error: Index out of bounds.");
        process.exit(-1);
    }

    const result = getValueFromArray(id_sequence, index);
    console.log(`Value at index ${index}: ${result}`);
    rl.close();
});
