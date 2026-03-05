// No imports required; console.log is built-in
function main() {
  console.log("Hello from JavaScript with no extra imports.");
}

if (require.main === module) {
  main();
}
