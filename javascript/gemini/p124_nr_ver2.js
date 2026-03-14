const args = process.argv.slice(2);

if (args.length !== 1) {
    console.error("Error: Exactly one argument required.");
    process.exit(1);
}

let input = args[0];
console.log(input);

input = input.trimEnd();
console.log(input);

process.exit(0);