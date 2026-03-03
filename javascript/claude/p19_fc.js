'use strict';

const args = process.argv.slice(2);

if (args.length < 1) {
    console.error(`Usage: node p19_fc.js <integer>`);
    process.exit(1);
}

const raw = args[0];
const parsed = Number(raw);

/* Reject non-integers, NaN, Infinity, and empty strings */
if (!Number.isInteger(parsed) || raw.trim() === '') {
    console.error(`Error: "${raw}" is not a valid integer.`);
    process.exit(1);
}

/* Overflow check: Number.MAX_SAFE_INTEGER is 2^53 - 1 */
if (parsed > Number.MAX_SAFE_INTEGER - 1000) {
    console.error(`Error: adding 1000 to ${parsed} exceeds safe integer range.`);
    process.exit(1);
}

const result = parsed + 1000;
console.log(result);
