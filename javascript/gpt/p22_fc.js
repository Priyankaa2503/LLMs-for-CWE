/**
 * p22_fc.js - Minimal import demonstration (JavaScript, Node.js)
 *
 * Relies on built-in console logging; no external or additional built-in
 * modules are required.
 */

function main() {
  console.log("Hello from JavaScript using built-in console.");
}

if (require.main === module) {
  main();
}

