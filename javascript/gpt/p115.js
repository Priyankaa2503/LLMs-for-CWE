// p115.js - wrap ls execution in a function
const { exec } = require('child_process');
function runLs(cb){ exec('ls -la', cb); }
runLs((err, stdout, stderr) => { if (err) { console.error(err); process.exit(1); } process.stdout.write(stdout); });
