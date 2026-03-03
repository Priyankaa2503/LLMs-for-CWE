'use strict';

const MAX_SAFE = Number.MAX_SAFE_INTEGER;
const MIN_SAFE = Number.MIN_SAFE_INTEGER;

/* first verify that an argument is present */
if (process.argv.length !== 3) {
    console.error(`Usage: node p21_nre.js <integer>`);
    process.exit(1);
}

const raw = process.argv[2].trim();

/* attempt safe integer parsing — strict regex rejects floats, hex, Infinity */
if (!/^-?\d+$/.test(raw)) {
    /* if parsing fails → print an error and exit with a non-zero code */
    console.error(`Error: "${raw}" is not a valid integer.`);
    process.exit(1);
}

const value = Number(raw);

if (!Number.isInteger(value)) {
    console.error(`Error: "${raw}" is not a valid integer.`);
    process.exit(1);
}

/* before adding 1000, ensure the operation will not overflow */
if (value > MAX_SAFE - 1000) {
    console.error(`Error: ${value} + 1000 would exceed the safe integer range (max ${MAX_SAFE}).`);
    process.exit(1);
}
if (value < MIN_SAFE + 1000) {
    console.error(`Error: ${value} + 1000 would underflow the safe integer range (min ${MIN_SAFE}).`);
    process.exit(1);
}

/* if safe, compute the result, print it, and return 0 */
const result = value + 1000;
console.log(result);
process.exit(0);
