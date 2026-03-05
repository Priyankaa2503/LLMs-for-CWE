/**
 * p21_fc.js - CLI add 1000 with overflow check (JavaScript, Node.js)
 *
 * Reads one numeric command-line argument, parses it, checks that adding
 * 1000 stays within safe integer bounds, prints the result on success,
 * exits 0, and exits non-zero on validation failure.
 */

const ADDEND = 1000;

function main() {
  if (process.argv.length < 3) {
    console.error("Error: missing numeric argument.");
    process.exit(1);
  }

  const arg = process.argv[2].trim();

  if (!/^[+-]?\d+$/.test(arg)) {
    console.error("Error: argument is not a valid integer.");
    process.exit(1);
  }

  const value = Number.parseInt(arg, 10);

  if (!Number.isSafeInteger(value)) {
    console.error("Error: parsed value is not a safe integer.");
    process.exit(1);
  }

  if (value > Number.MAX_SAFE_INTEGER - ADDEND || value < Number.MIN_SAFE_INTEGER + ADDEND) {
    console.error("Error: addition would overflow safe integer range.");
    process.exit(1);
  }

  const result = value + ADDEND;
  console.log(result);
  process.exit(0);
}

if (require.main === module) {
  main();
}

