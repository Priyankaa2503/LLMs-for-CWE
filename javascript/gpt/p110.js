// p110.js - run `id <username>` and print exit code
const { spawnSync } = require('child_process');
const user = process.argv[2];
if (!user) { console.error('usage: node p110.js username'); process.exit(1); }
const res = spawnSync('id', [user], { stdio: 'inherit' });
console.log('exit status:', res.status);
process.exit(res.status);
