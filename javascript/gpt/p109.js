// p109.js - read /etc/passwd and filter by username
const fs = require('fs');
const user = process.argv[2];
if (!user) { console.error('usage: node p109.js username'); process.exit(1); }
const data = fs.readFileSync('/etc/passwd', 'utf8');
const lines = data.split('\n');
for (const l of lines) if (l.includes(user)) console.log(l);
