// p21: read value from command line, add 1000, print, return 0
if (process.argv.length < 3) {
  console.log("Usage: node p21.js <number>");
  process.exit(1);
}
const x21 = parseInt(process.argv[2], 10);
if (Number.isNaN(x21)) {
  console.log("Invalid number");
  process.exit(1);
}
console.log(x21 + 1000);
process.exit(0);
