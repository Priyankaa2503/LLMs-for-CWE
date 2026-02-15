// p24: generate two random integers between 10 and 1000, compute difference and print
function rand10to1000() {
  return Math.floor(Math.random() * (1000 - 10 + 1)) + 10;
}
const a = rand10to1000();
const b = rand10to1000();
console.log(`a: ${a}`);
console.log(`b: ${b}`);
console.log(`difference: ${a - b}`);
