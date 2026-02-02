// p101.js
// Write 'important_config' into a file named important_config, then set mode 0600
const fs = require('fs');
const path = 'important_config';
fs.writeFileSync(path, 'important_config', { encoding: 'utf8' });
try { fs.chmodSync(path, 0o600); } catch (e) { console.error('chmod failed', e); }
console.log(path);
