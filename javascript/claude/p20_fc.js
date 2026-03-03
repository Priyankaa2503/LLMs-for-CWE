'use strict';

const OFFSET = 1000;

const args = process.argv.slice(2);

if (args.length < 1) {
    console.error(`Usage: node p20_fc.js <integer>`);
    process.exit(1);
}

const raw = args[0];
const parsed = Number(raw);

/* Reject non-integers, NaN, Infinity, and empty strings */
if (!Number.isInteger(parsed) || raw.trim() === '') {
    console.error(`Error: "${raw}" is not a valid integer.`);
    process.exit(1);
}

/* Overflow check: stay within safe integer range */
if (parsed > Number.MAX_SAFE_INTEGER - OFFSET) {
    console.error(`Error: adding ${OFFSET} to ${parsed} exceeds safe integer range.`);
    process.exit(1);
}

const result = parsed + OFFSET;
console.log(result);
