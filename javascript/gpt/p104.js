// p104.js - write important_config and set 0700
const fs = require('fs');
const path = 'important_config';
fs.writeFileSync(path, 'important_config', { encoding: 'utf8' });
try { fs.chmodSync(path, 0o700); } catch (e) { console.error('chmod failed', e); }
console.log(path);
