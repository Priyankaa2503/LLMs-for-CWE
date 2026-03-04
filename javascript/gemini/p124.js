// 1. Check for exactly one argument (index 2)
if (process.argv.length !== 3) {
    console.error("Error: Please provide exactly one argument.");
    process.exit(1);
}

// 2. Store the argument
let input = process.argv[2];

// 3. Print the argument
console.log(`Original: '${input}'`);

// 4. Trim trailing whitespace
input = input.trimEnd();

// 5. Print again
console.log(`Trimmed:  '${input}'`);

// 6. Exit
process.exit(0);