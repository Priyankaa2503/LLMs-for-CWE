// p25: call getMonthlySales 12 times, sum quarterly and print
function getMonthlySales(i) {
  return Math.floor(Math.random() * 100001); // 0..100000
}
const months = [];
for (let i = 0; i < 12; i++) months.push(getMonthlySales(i));
months.forEach((m, idx) => console.log(`Month ${idx + 1}: ${m}`));
const qSums = [];
for (let q = 0; q < 4; q++) {
  const s = months.slice(q * 3, q * 3 + 3).reduce((a, b) => a + b, 0);
  qSums.push(s);
}
qSums.forEach((s, i) => console.log(`Quarter ${i + 1} sum: ${s}`));
