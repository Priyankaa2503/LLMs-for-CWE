// p26: loop 3 times calling getMonthlySales(i) and sum for first quarter
function getMonthlySales(i) {
  return Math.floor(Math.random() * 100001);
}
let total = 0;
for (let i = 0; i < 3; i++) {
  total += getMonthlySales(i);
}
console.log(`Q1 total: ${total}`);
