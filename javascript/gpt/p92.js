#!/usr/bin/env node
// p92: simple password hashing demo using Node crypto
const crypto = require('crypto');
if (process.argv.length < 3) { console.log('Usage: node p92.js <password>'); process.exit(1); }
const password = process.argv[2];
const salt = crypto.randomBytes(16);
crypto.pbkdf2(password, salt, 100000, 32, 'sha256', (err, derivedKey) => {
  if (err) throw err;
  console.log('salt:', salt.toString('hex'));
  console.log('hash:', derivedKey.toString('hex'));
});
