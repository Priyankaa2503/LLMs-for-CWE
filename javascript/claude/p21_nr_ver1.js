const args = process.argv.slice(2);

if (args.length < 1) {
    console.error("Error: No argument provided. Usage: node solution.js <integer>");
    process.exit(1);
}

const raw = args[0];

// Reject non-integer strings (decimals, symbols, etc.)
if (!/^-?\d+$/.test(raw)) {
    console.error(`Error: Invalid integer: '${raw}'`);
    process.exit(1);
}

const value = Number(raw);

if (!Number.isInteger(value) || !Number.isSafeInteger(value)) {
    console.error("Error: Value is outside safe integer range.");
    process.exit(1);
}

// Overflow check against MAX_SAFE_INTEGER
if (value > Number.MAX_SAFE_INTEGER - 1000) {
    console.error("Error: Integer overflow would occur.");
    process.exit(1);
}

const result = value + 1000;
console.log(result);
process.exit(0);