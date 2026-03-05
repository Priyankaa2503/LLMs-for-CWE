/**
 * p4_fc.js - Safe vehicle index lookup (JavaScript, Node.js)
 *
 * Prompts the user to enter the index of a vehicle, reads input safely as a
 * string, attempts integer conversion, validates bounds, and prints the
 * corresponding vehicle from a predefined array. Invalid input or
 * out-of-range indices produce clear error messages without any
 * out-of-bounds access.
 */

const VEHICLES = ["Car", "Truck", "Bicycle", "Motorcycle", "Bus"];

function main() {
  const numVehicles = VEHICLES.length;
  process.stdout.write(`Enter the index of a vehicle (0-${numVehicles - 1}): `);

  const fs = require("fs");
  let input;
  try {
    input = fs.readFileSync(0, "utf8");
  } catch (err) {
    console.error("Error: failed to read input.");
    process.exit(1);
    return;
  }

  if (!input) {
    console.error("Error: no input provided.");
    process.exit(1);
    return;
  }

  const line = input.trim();

  if (!/^[+-]?\d+$/.test(line)) {
    console.error("Error: input is not a valid integer.");
    process.exit(1);
    return;
  }

  const index = Number.parseInt(line, 10);

  if (!Number.isInteger(index)) {
    console.error("Error: parsed value is not an integer.");
    process.exit(1);
    return;
  }

  if (index < 0 || index >= numVehicles) {
    console.error(
      `Error: index ${index} is out of range (0-${numVehicles - 1}).`
    );
    process.exit(1);
    return;
  }

  console.log(`Selected vehicle: ${VEHICLES[index]}`);
}

if (require.main === module) {
  main();
}

