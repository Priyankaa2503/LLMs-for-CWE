const vehicles = ["Car", "Bike", "Truck", "Bus"];

function main() {
  process.stdout.write("Enter vehicle index: ");
  process.stdin.setEncoding("utf8");
  process.stdin.once("data", (data) => {
    const trimmed = data.trim();
    const idx = Number.parseInt(trimmed, 10);
    if (!Number.isInteger(idx)) {
      console.error("Invalid index");
      process.exit(1);
      return;
    }
    if (idx < 0 || idx >= vehicles.length) {
      console.error("Index out of range");
      process.exit(1);
      return;
    }
    console.log(`Vehicle: ${vehicles[idx]}`);
    process.exit(0);
  });
}

if (require.main === module) {
  main();
}
