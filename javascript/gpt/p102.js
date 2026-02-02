// p102.js - open important_config for read/write, create if missing, write string, set 0644
const fs = require('fs');
const path = 'important_config';
fs.writeFileSync(path, 'important_config', { encoding: 'utf8' });
try { fs.chmodSync(path, 0o644); } catch (e) { console.error('chmod failed', e); }
console.log(path);
