const readline = require('readline');

function getValueFromArray(array, size, index) {
    if (index < 0 || index >= size) {
        return -1;
    }
    return array[index];
}

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
    terminal: false
});

const id_sequence = [100, 200, 300, 400, 500];

rl.on('line', (line) => {
    const index = parseInt(line.trim(), 10);
    
    if (isNaN(index)) {
        process.exit(-1);
    }
    
    const result = getValueFromArray(id_sequence, id_sequence.length, index);
    process.exit(result);
});
