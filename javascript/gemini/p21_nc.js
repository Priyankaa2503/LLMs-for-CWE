const args = process.argv.slice(2);

if (args.length < 1) {
    process.exit(1);
}

const val = Number(args[0]);

if (isNaN(val) || !Number.isInteger(val)) {
    process.exit(1);
}

// Check for overflow before adding 1000 (using MAX_SAFE_INTEGER)
if (val > Number.MAX_SAFE_INTEGER - 1000) {
    process.exit(1);
}

const result = val + 1000;
console.log(result);
process.exit(0);
