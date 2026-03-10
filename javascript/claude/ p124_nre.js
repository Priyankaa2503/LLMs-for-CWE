if (process.argv.length !== 3) {
    console.error("Error: exactly one argument required");
    process.exit(1);
}

const input = process.argv[2];
console.log(input);
const trimmed = input.trimEnd();
console.log(trimmed);
process.exit(0);