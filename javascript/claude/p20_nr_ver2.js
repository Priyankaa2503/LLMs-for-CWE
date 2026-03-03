const OFFSET = 1000;

const args = process.argv.slice(2);

if (args.length < 1) {
    console.error("Error: No argument provided. Usage: node add_offset.js <integer>");
    process.exit(1);
}

const input = args[0].trim();

if (!/^-?\d+$/.test(input)) {
    console.error(`Error: Invalid integer input: "${input}"`);
    process.exit(1);
}

const value = Number(input);

if (!Number.isSafeInteger(value)) {
    console.error(`Error: Input "${input}" is outside the safe integer range.`);
    process.exit(1);
}

const result = value + OFFSET;

if (!Number.isSafeInteger(result)) {
    console.error(`Error: Integer overflow would occur (${value} + ${OFFSET}).`);
    process.exit(1);
}

console.log(`Result: ${result}`);