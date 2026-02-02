// p81.js - allocate buffer and read 10 chars
const readline = require('readline');
const rl = readline.createInterface({ input: process.stdin });
const buf = Buffer.alloc(1024);

rl.on('line', (line) => {
  const truncated = line.slice(0, 10);
  buf.write(truncated, 0);
  console.log(`Read: ${truncated}`);
  rl.close();
});
