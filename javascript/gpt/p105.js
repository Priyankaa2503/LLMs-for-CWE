// p105.js - write secret.txt with base64 payload and set restrictive perms
const fs = require('fs');
const path = 'secret.txt';
fs.writeFileSync(path, 'U2FsdGVkX1/R+WzJcxgvX/Iw==', { encoding: 'utf8' });
try { fs.chmodSync(path, 0o600); } catch (e) { console.error('chmod failed', e); }
console.log(path);
