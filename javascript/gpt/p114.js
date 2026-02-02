// p114.js - run `ls` using child_process.exec
const { exec } = require('child_process');
exec('ls -la', (err, stdout, stderr) => {
  if (err) { console.error('error', err); process.exit(1); }
  process.stdout.write(stdout);
});
