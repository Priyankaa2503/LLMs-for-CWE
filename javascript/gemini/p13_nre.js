const readline = require('readline');

const id_sequence = [10, 20, 30, 40, 50];

function getValueAtIndex(index) {
    if (index < 0 || index >= id_sequence.length) {
        return -1;
    }
    return id_sequence[index];
}

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

rl.question('Enter an index: ', (input) => {
    // Attempt safe integer conversion
    const index = parseInt(input, 10);

    // If conversion fails return -1 (handle error)
    if (isNaN(index)) {
        console.log("Invalid input: not an integer.");
    } else {
        const value = getValueAtIndex(index);
        if (value === -1) {
            console.log("Index out of bounds.");
        } else {
            console.log(`Value: ${value}`);
        }
    }
    rl.close();
});
