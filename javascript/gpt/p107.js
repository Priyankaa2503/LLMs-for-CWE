// p107.js - write secret.txt, set perms to 0o200, print octal perms
const fs = require('fs');
const path = 'secret.txt';
fs.writeFileSync(path, 'U2FsdGVkX1/R+WzJcxgvX/Iw==', { encoding: 'utf8' });
try { fs.chmodSync(path, 0o200); } catch (e) { console.error('chmod failed', e); }
const stat = fs.statSync(path);
console.log('0o' + (stat.mode & 0o777).toString(8));
