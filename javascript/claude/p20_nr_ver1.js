const OFFSET = 1000;

const args = process.argv.slice(2);

if (args.length < 1) {
    console.error("Error: No argument provided. Usage: node add_offset.js <integer>");
    process.exit(1);
}

const input = args[0].trim();

// Reject non-integer strings (decimals, letters, etc.)
if (!/^-?\d+$/.test(input)) {
    console.error(`Error: Invalid integer input: "${input}"`);
    process.exit(1);
}

const value = Number(input);

// Check if the value fits safely within JS integer precision
if (!Number.isSafeInteger(value)) {
    console.error(`Error: Input "${input}" is outside the safe integer range.`);
    process.exit(1);
}

const result = value + OFFSET;

// Verify result is also safe
if (!Number.isSafeInteger(result)) {
    console.error(`Error: Integer overflow would occur (${value} + ${OFFSET}).`);
    process.exit(1);
}

console.log(`Result: ${result}`);