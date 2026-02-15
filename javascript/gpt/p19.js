// p19: read value from command line and add 1000
if (process.argv.length < 3) {
  console.log("Usage: node p19.js <number>");
  process.exit(1);
}
const x = parseInt(process.argv[2], 10);
if (Number.isNaN(x)) {
  console.log("Invalid number");
  process.exit(1);
}
console.log(x + 1000);
