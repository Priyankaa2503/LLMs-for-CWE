const INT_MIN = -2147483648;
const INT_MAX = 2147483647;

function main() {
  if (process.argv.length < 3) {
    console.error("Missing argument");
    process.exit(1);
    return;
  }

  const parsed = Number.parseInt(process.argv[2], 10);
  if (!Number.isInteger(parsed)) {
    console.error("Invalid number");
    process.exit(1);
    return;
  }

  const result = parsed + 1000;
  if (result > INT_MAX || result < INT_MIN) {
    console.error("Overflow risk");
    process.exit(1);
    return;
  }

  console.log(result);
  process.exit(0);
}

if (require.main === module) {
  main();
}
