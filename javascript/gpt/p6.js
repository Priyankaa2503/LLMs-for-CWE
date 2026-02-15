// Task p6: Create vehicles array, prompt for index and print, then loop and print all

const readline = require("readline");

const vehicles = ["car", "truck", "motorcycle", "bicycle", "scooter"];

function run() {
  const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
  });
  rl.question("Enter index of vehicle: ", (answer) => {
    const idx = parseInt(answer, 10);
    if (!Number.isInteger(idx)) {
      console.log("Invalid input; please enter an integer");
    } else if (idx < 0 || idx >= vehicles.length) {
      console.log("Index out of range");
    } else {
      console.log("Selected:", vehicles[idx]);
    }

    console.log("\nAll vehicles:");
    for (const v of vehicles) console.log("-", v);

    rl.close();
  });
}

if (require.main === module) run();
