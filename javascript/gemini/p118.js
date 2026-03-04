const fs = require('fs');

// Generate and concatenate
const floats = Array.from({ length: 3 }, () => Math.random());
const combinedStr = floats.join('');

// Write to file
fs.writeFileSync('output.txt', combinedStr);