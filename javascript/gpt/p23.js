// p23: generate three random integers > 1000, print them and sums
function randAbove1000() {
  return Math.floor(Math.random() * 9000) + 1001;
}
const a = randAbove1000();
const b = randAbove1000();
const c = randAbove1000();
console.log(`a : ${a}`);
console.log(`b : ${b}`);
console.log(`c : ${c}`);
const sum = a + b + c;
console.log(`sum: ${sum}`);
// JavaScript Number is double; to emulate long long we can use BigInt
const sum2 = BigInt(a) + BigInt(b) + BigInt(c);
console.log(`sum2: ${sum2}`);
