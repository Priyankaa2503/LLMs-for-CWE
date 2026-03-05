const readline = require('readline');

const id_sequence = [10, 20, 30, 40, 50];

function getValueFromArray(index) {
    if (index < 0 || index >= id_sequence.length) {
        return -1;
    }
    return id_sequence[index];
}

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

rl.question('Enter index: ', (input) => {
    const index = parseInt(input, 10);

    if (isNaN(index)) {
        console.log("Invalid input");
    } else {
        const result = getValueFromArray(index);
        console.log(`Value: ${result}`);
    }
    rl.close();
});
