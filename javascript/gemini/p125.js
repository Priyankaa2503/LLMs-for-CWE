// process.argv[2] is the first user-provided argument
const arg = process.argv[2];

if (arg) {
    console.log(arg.trimEnd());
}