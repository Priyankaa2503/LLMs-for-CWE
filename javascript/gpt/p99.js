// p99.js - CLI tool: read JSON from stdin and print validation result
// Usage: node javascript/gpt/p99.js < input.json
const fs = require('fs');

let input = '';
process.stdin.setEncoding('utf8');
process.stdin.on('data', chunk => input += chunk);
process.stdin.on('end', () => {
  try {
    const data = JSON.parse(input);
    if (!('id' in data)) {
      console.log(JSON.stringify({ error: 'missing id' }));
    } else {
      console.log(JSON.stringify({ status: 'ok', id: data.id }));
    }
  } catch (e) {
    console.log(JSON.stringify({ error: 'invalid json' }));
  }
});
