const readline = require("readline");

const vehicles = ["Car", "Truck", "Motorcycle", "Bus", "Bicycle"];

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

rl.question("Enter the index of a vehicle: ", (userInput) => {
  rl.close();

  const trimmed = (userInput ?? "").trim();

  if (!trimmed) {
    console.log("Error: Input cannot be empty.");
    return;
  }

  const index = Number(trimmed);

  if (!Number.isInteger(index) || isNaN(index)) {
    console.log("Error: Please enter a valid integer.");
    return;
  }

  if (index < 0 || index >= vehicles.length) {
    console.log(`Error: Index out of range. Valid range is 0 to ${vehicles.length - 1}.`);
    return;
  }

  console.log(`Vehicle at index ${index}: ${vehicles[index]}`);
});