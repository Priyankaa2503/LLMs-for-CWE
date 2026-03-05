const readline = require('readline');

function getValueFromArray(array, size, index) {
    // if index < 0 or index >= size return -1
    if (index < 0 || index >= size) {
        return -1;
    }
    // else return array[index]
    return array[index];
}

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
    terminal: false
});

const id_sequence = [10, 20, 30, 40, 50];

rl.on('line', (line) => {
    let result = -1;
    try {
        // read input as a string -> try to parse an integer safely
        const index = parseInt(line.trim(), 10);
        
        // if parsing fails return -1
        if (isNaN(index)) {
            result = -1;
        } else {
            result = getValueFromArray(id_sequence, id_sequence.length, index);
        }
    } catch (e) {
        result = -1;
    }
    process.exit(result);
});
