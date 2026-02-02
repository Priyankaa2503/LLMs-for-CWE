// p108.js
// Usage: node javascript/gpt/p108.js username
const { execFile } = require('child_process');
const user = process.argv[2];
if (!user) { console.error('usage: node p108.js username'); process.exit(1); }
execFile('getent', ['passwd', user], (err, stdout, stderr) => {
  if (err) {
    if (err.code === 'ENOENT') console.error('getent not found');
    else console.error(err.message);
    process.exit(1);
  }
  process.stdout.write(stdout);
});
