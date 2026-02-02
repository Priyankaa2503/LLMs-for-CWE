// p79.js - allocate two buffers and read lines from stdin
const readline = require('readline');
const rl = readline.createInterface({ input: process.stdin });

const buf = Buffer.alloc(1024);
const buf1 = Buffer.alloc(1024);

let lineCount = 0;
rl.on('line', (line) => {
  if (lineCount === 0) {
    buf.write(line.slice(0, 100), 0);
    console.log(`Read: ${line}`);
    lineCount++;
  } else if (lineCount === 1) {
    buf1.write(line.slice(0, 100), 0);
    console.log(`Read: ${line}`);
    rl.close();
  }
});
