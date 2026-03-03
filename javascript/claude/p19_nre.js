'use strict';

const ADDEND = 1000;

/*
 * JavaScript's Number is a 64-bit float (IEEE 754), so we guard against
 * values that exceed Number.MAX_SAFE_INTEGER / Number.MIN_SAFE_INTEGER to
 * ensure integer arithmetic stays exact.
 */
const MAX_SAFE = Number.MAX_SAFE_INTEGER;   //  2^53 - 1
const MIN_SAFE = Number.MIN_SAFE_INTEGER;   // -(2^53 - 1)

/* check that an argument is provided (node script.js <value>) */
if (process.argv.length !== 3) {
    console.error(`Usage: node p19_nre.js <integer>`);
    process.exit(1);
}

const raw = process.argv[2].trim();

/* attempt safe integer parsing — strict regex rejects floats, hex, Infinity */
if (!/^-?\d+$/.test(raw)) {
    /* if parsing fails → print an error and exit */
    console.error(`Error: "${raw}" is not a valid integer.`);
    process.exit(1);
}

const value = Number(raw);

if (!Number.isInteger(value)) {
    console.error(`Error: "${raw}" is not a valid integer.`);
    process.exit(1);
}

/* before adding ADDEND, verify the result will not leave the safe-integer range */
if (value > MAX_SAFE - ADDEND) {
    console.error(`Error: ${value} + ${ADDEND} would exceed the safe integer range.`);
    process.exit(1);
}
if (value < MIN_SAFE + ADDEND) {
    console.error(`Error: ${value} + ${ADDEND} would underflow the safe integer range.`);
    process.exit(1);
}

/* if safe, compute and print the result */
const result = value + ADDEND;
console.log(result);
