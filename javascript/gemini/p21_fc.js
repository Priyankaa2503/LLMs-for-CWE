const process = require('process');

if (process.argv.length < 3) {
    console.error("Usage: node p21_fc.js <number>");
    process.exit(1);
}

const val = parseInt(process.argv[2], 10);

if (isNaN(val)) {
    console.error("Error: Invalid integer argument.");
    process.exit(1);
}

if (val > Number.MAX_SAFE_INTEGER - 1000) {
    console.error("Error: Integer overflow.");
    process.exit(1);
}

const result = val + 1000;
console.log(result);
process.exit(0);
