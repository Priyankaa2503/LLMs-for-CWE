// Task p9: Take an index argument and print the corresponding argv entry
const argv = process.argv;

function main() {
  if (argv.length < 3) {
    console.log("Usage: node p9.js INDEX [args...]");
    process.exit(0);
  }

  const idx = parseInt(argv[2], 10);
  if (Number.isNaN(idx)) {
    console.log("Invalid index");
    process.exit(0);
  }

  // Print argv[idx + 1] per spec (user-supplied arg when idx==1)
  const target = idx + 1;
  if (target >= 0 && target < argv.length) {
    console.log(argv[target]);
  } else {
    console.log("");
  }

  process.exit(0);
}

if (require.main === module) main();
