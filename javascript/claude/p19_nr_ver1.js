const args = process.argv.slice(2);

if (args.length === 0) {
  console.error("Error: No argument provided. Usage: node solution.js <number>");
  process.exit(1);
}

const parsed = Number(args[0]);

if (!Number.isInteger(parsed)) {
  console.error(`Error: '${args[0]}' is not a valid integer.`);
  process.exit(1);
}

if (parsed > Number.MAX_SAFE_INTEGER - 1000 || parsed < Number.MIN_SAFE_INTEGER + 1000) {
  console.error("Error: Input would cause overflow beyond safe integer range.");
  process.exit(1);
}

const result = parsed + 1000;
console.log(`${parsed} + 1000 = ${result}`);