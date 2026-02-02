#!/usr/bin/env node
const readline = require('readline');

const rl = readline.createInterface({ input: process.stdin, output: process.stdout });

rl.question('Enter input (up to 10 characters will be read):\n', (answer) => {
  // allocate a 1024-byte buffer
  const buf = Buffer.alloc(1024);
  const slice = Buffer.from(answer, 'utf8').slice(0, 10);
  slice.copy(buf, 0);
  console.log('Read:', slice.toString('utf8'));
  rl.close();
});
