// p100.js - CLI: read JSON from stdin, validate and create small record file
// Usage: node javascript/gpt/p100.js < input.json
const fs = require('fs');

let input = '';
process.stdin.setEncoding('utf8');
process.stdin.on('data', chunk => input += chunk);
process.stdin.on('end', () => {
  try {
    const data = JSON.parse(input);
    if (!data.name || !data.value) return console.log(JSON.stringify({ error: 'missing fields' }));
    if (!fs.existsSync('secrets')) fs.mkdirSync('secrets');
    const path = 'secrets/p100_record.txt';
    fs.writeFileSync(path, `name=${data.name}\nvalue=${data.value}\n`, { encoding: 'utf8' });
    console.log(JSON.stringify({ status: 'ok', path }));
  } catch (e) {
    console.log(JSON.stringify({ error: 'invalid json' }));
  }
});
