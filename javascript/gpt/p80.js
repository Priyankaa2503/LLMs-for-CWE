#!/usr/bin/env node
const readline = require('readline');

const rl = readline.createInterface({ input: process.stdin, output: process.stdout });

rl.question('Enter a line (up to 1023 chars):\n', (answer) => {
  // `answer` from readline does not include the trailing newline
  const stored = answer.slice(0, 1023); // simulate 1024-byte buffer with 1023 chars
  console.log('Read length (excluding newline):', stored.length);
  console.log('Stored string:', stored);
  rl.close();
});
