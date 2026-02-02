#!/usr/bin/env node
// p96: write secret file and set restrictive permissions
const fs = require('fs');
const filename = 'secret.txt';
const secret = 'U2FsdGVkX1/R+WzJcxgvX/Iw==';
fs.writeFileSync(filename, secret);
// set owner read-only (0400)
fs.chmodSync(filename, 0o400);
console.log('Wrote', filename);
