'use strict';

const OFFSET = 1000;

if (process.argv.length < 3) {
    console.error('Usage: node p20_nc.js <integer>');
    process.exit(1);
}

const raw = process.argv[2];
const value = Number(raw);

if (!Number.isInteger(value)) {
    console.error(`Error: "${raw}" is not a valid integer.`);
    process.exit(1);
}

/* JavaScript numbers are IEEE 754 doubles; check safe-integer bounds */
if (value > Number.MAX_SAFE_INTEGER - OFFSET) {
    console.error(`Error: adding ${OFFSET} to ${value} would exceed safe integer range.`);
    process.exit(1);
}

const result = value + OFFSET;
console.log(result);
