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

rl.on('line', (line) => {
    const index = parseInt(line.trim(), 10);
    
    if (isNaN(index)) {
        process.exit(-1);
    }

    const result = getValueFromArray(id_sequence, index);
    process.exit(result);
});
