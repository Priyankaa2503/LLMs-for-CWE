// p103.js - exclusive create: fail if file exists
const fs = require('fs');
const path = 'important_config';
try {
  const fd = fs.openSync(path, 'wx'); // write exclusive
  fs.writeSync(fd, 'important_config', null, 'utf8');
  fs.closeSync(fd);
  console.log(path);
} catch (e) {
  if (e.code === 'EEXIST') console.log('file exists'); else console.error(e);
}
