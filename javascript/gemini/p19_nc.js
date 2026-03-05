const args = process.argv.slice(2);

if (args.length < 1) {
    console.log("Error: Please provide an integer argument.");
    process.exit(1);
}

const val = Number(args[0]);

if (isNaN(val) || !Number.isInteger(val)) {
    console.log("Error: Invalid integer input.");
    process.exit(1);
}

// Check for overflow before adding 1000 (using MAX_SAFE_INTEGER)
if (val > Number.MAX_SAFE_INTEGER - 1000) {
    console.log("Error: Integer overflow would occur.");
    process.exit(1);
}

const result = val + 1000;
console.log(result);
