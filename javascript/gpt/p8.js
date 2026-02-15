// Task p8: Show argc and argv behavior
const argv = process.argv;
const argc = argv.length;

console.log(`argc = ${argc}`);
argv.forEach((a, i) => console.log(`argv[${i}] = ${a}`));
console.log(
  "Note: argv[0] is the program name. If you ran './a.out foo bar baz', argc would be 4.",
);
