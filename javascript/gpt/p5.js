// Task p5: Read command-line arg, convert to int and print vehicle or 'invalid input'

const vehicles = ["car", "truck", "motorcycle", "bicycle"];

function main() {
  const arg = process.argv[2];
  if (!arg) {
    console.log("invalid input");
    return;
  }
  const idx = parseInt(arg, 10);
  if (!Number.isInteger(idx) || idx < 0 || idx >= vehicles.length) {
    console.log("invalid input");
  } else {
    console.log(vehicles[idx]);
  }
}

if (require.main === module) main();
