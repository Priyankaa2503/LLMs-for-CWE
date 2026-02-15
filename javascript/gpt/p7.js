// Task p7: Convert argv[1] to integer and print argv[INDEX]
const argv = process.argv;

function main() {
  if (argv.length < 3) {
    console.log("Usage: node p7.js INDEX [args...]");
    process.exit(0);
  }

  const idx = parseInt(argv[2], 10);
  if (Number.isNaN(idx)) {
    console.log("Invalid INDEX");
    process.exit(0);
  }

  if (idx >= 0 && idx < argv.length) {
    console.log(argv[idx]);
  } else {
    // Print nothing per spec
    console.log("");
  }

  process.exit(0);
}

if (require.main === module) main();
