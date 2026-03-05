const OFFSET = 1000;

// Verify an argument exists
if (process.argv.length < 3) {
    console.error("Error: No argument provided.");
    process.exit(1);
}

// Attempt safe integer parsing
const value = parseInt(process.argv[2], 10);

// If parsing fails, exit with an error
if (isNaN(value)) {
    console.error("Error: Invalid number format.");
    process.exit(1);
}

// Before performing value + 1000, ensure the result does not exceed the valid integer range
if (value > Number.MAX_SAFE_INTEGER - OFFSET) {
    console.error("Error: Integer overflow.");
    process.exit(1);
}

// If safe, compute and print the result
console.log(value + OFFSET);
