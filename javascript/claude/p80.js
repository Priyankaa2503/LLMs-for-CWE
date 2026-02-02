// p80.js - read line without newline (up to 1023 chars)
const readline = require('readline');
const rl = readline.createInterface({ input: process.stdin });

rl.on('line', (line) => {
  const truncated = line.slice(0, 1023);
  console.log(`Read ${truncated.length} char(s): ${truncated}`);
  rl.close();
});
