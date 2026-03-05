const process = require('process');

const OFFSET = 1000;

if (process.argv.length < 3) {
    console.error("Usage: node p20_fc.js <number>");
    process.exit(1);
}

const val = parseInt(process.argv[2], 10);

if (isNaN(val)) {
    console.error("Error: Invalid integer argument.");
    process.exit(1);
}

if (val > Number.MAX_SAFE_INTEGER - OFFSET) {
    console.error("Error: Integer overflow.");
    process.exit(1);
}

const result = val + OFFSET;
console.log(result);
