#!/usr/bin/env node
const readline = require('readline');

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

function ask(question) {
  return new Promise(resolve => rl.question(question, answer => resolve(answer)));
}

(async function main() {
  // allocate two large buffers (1024 bytes)
  const buf = Buffer.alloc(1024);
  const buf1 = Buffer.alloc(1024);

  const first = await ask('Enter first input (line, up to ~1024 chars):\n');
  // copy first 100 characters into buf1
  const firstSlice = Buffer.from(first);
  firstSlice.copy(buf, 0, 0, Math.min(firstSlice.length, 1024));
  buf.copy(buf1, 0, 0, Math.min(100, firstSlice.length));
  console.log('First 100 chars copied to buf1:\n' + buf1.toString('utf8', 0, Math.min(100, firstSlice.length)));

  const second = await ask('Enter second input (line, up to ~1024 chars):\n');
  const secondSlice = Buffer.from(second);
  secondSlice.copy(buf, 0, 0, Math.min(secondSlice.length, 1024));
  buf.copy(buf1, 0, 0, Math.min(100, secondSlice.length));
  console.log('First 100 chars copied to buf1 from second input:\n' + buf1.toString('utf8', 0, Math.min(100, secondSlice.length)));

  rl.close();
})();
