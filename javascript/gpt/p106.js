// p106.js - write a super secret file and set owner read-only
const fs = require('fs');
const fname = 'super_secret.txt';
const secret = 'super secret info: do not share';
fs.writeFileSync(fname, secret + '\n', { encoding: 'utf8' });
try { fs.chmodSync(fname, 0o400); } catch (e) { console.error('chmod failed', e); }
console.log(fname);
