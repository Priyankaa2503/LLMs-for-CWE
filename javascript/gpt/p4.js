// Task p4: Prompt user for vehicle index and print vehicle

const readline = require("readline");

const vehicles = ["car", "truck", "motorcycle", "bicycle", "scooter"];

function askIndex() {
  const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
  });
  rl.question("Enter index of vehicle: ", (answer) => {
    const i = parseInt(answer, 10);
    if (!Number.isInteger(i)) {
      console.log("Invalid input; please enter an integer");
    } else if (i < 0 || i >= vehicles.length) {
      console.log("Index out of range");
    } else {
      console.log("Selected vehicle:", vehicles[i]);
    }
    rl.close();
  });
}

if (require.main === module) askIndex();
