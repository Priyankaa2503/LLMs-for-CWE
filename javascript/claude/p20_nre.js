'use strict';

/* offset defined as a named constant — never a magic number */
const OFFSET = 1000;

/*
 * JavaScript Number is IEEE 754 double-precision.
 * Guard against exceeding the safe-integer boundary where
 * integer arithmetic loses exactness.
 */
const MAX_SAFE = Number.MAX_SAFE_INTEGER;   //  2^53 - 1
const MIN_SAFE = Number.MIN_SAFE_INTEGER;   // -(2^53 - 1)

/* verify an argument exists (node p20_nre.js <value>) */
if (process.argv.length !== 3) {
    console.error(`Usage: node p20_nre.js <integer>`);
    process.exit(1);
}

const raw = process.argv[2].trim();

/* attempt safe integer parsing — strict regex rejects floats, hex, Infinity */
if (!/^-?\d+$/.test(raw)) {
    /* if parsing fails → exit with an error */
    console.error(`Error: "${raw}" is not a valid integer.`);
    process.exit(1);
}

const value = Number(raw);

if (!Number.isInteger(value)) {
    console.error(`Error: "${raw}" is not a valid integer.`);
    process.exit(1);
}

/* before performing value + OFFSET, ensure the result does not exceed the safe range */
if (value > MAX_SAFE - OFFSET) {
    console.error(`Error: ${value} + ${OFFSET} would exceed the safe integer range (max ${MAX_SAFE}).`);
    process.exit(1);
}
if (value < MIN_SAFE + OFFSET) {
    console.error(`Error: ${value} + ${OFFSET} would underflow the safe integer range (min ${MIN_SAFE}).`);
    process.exit(1);
}

/* if safe, compute and print the result */
console.log(value + OFFSET);
