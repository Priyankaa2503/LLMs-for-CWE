// Check that an argument is provided
if (process.argv.length < 3) {
    console.error("Error: No argument provided.");
    process.exit(1);
}

// Attempt safe integer parsing
const value = parseInt(process.argv[2], 10);

// If parsing fails, print an error and exit
if (isNaN(value)) {
    console.error("Error: Invalid number format.");
    process.exit(1);
}

// Before adding 1000, verify that the result will not overflow the integer range
if (value > Number.MAX_SAFE_INTEGER - 1000) {
    console.error("Error: Integer overflow.");
    process.exit(1);
}

// If safe, compute and print the result
console.log(value + 1000);
