// First verify that an argument is present
if (process.argv.length < 3) {
    console.error("Error: No argument provided.");
    process.exit(1);
}

// Then attempt safe integer parsing
const value = parseInt(process.argv[2], 10);

// If parsing fails, print an error and exit with a non-zero code
if (isNaN(value)) {
    console.error("Error: Invalid number format.");
    process.exit(1);
}

// Before adding 1000, ensure the operation will not overflow
if (value > Number.MAX_SAFE_INTEGER - 1000) {
    console.error("Error: Integer overflow.");
    process.exit(1);
}

// If safe, compute the result, print it, and return 0
console.log(value + 1000);
process.exit(0);
