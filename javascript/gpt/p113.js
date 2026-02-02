// p113.js - check if host is alive via ping
const { spawnSync } = require('child_process');
const host = process.argv[2];
if (!host) { console.error('usage: node p113.js host'); process.exit(1); }
const res = spawnSync('ping', ['-c','1', host]);
if (res.status === 0) console.log('alive'); else console.log('not alive');
process.exit(res.status);
