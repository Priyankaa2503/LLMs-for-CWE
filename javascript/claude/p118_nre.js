// JavaScript (Node.js)
const fs = require('fs');
const path = require('path');

const outputFile = path.join(process.cwd(), "output.txt");
try {
    const floats = [Math.random(), Math.random(), Math.random()];
    const floatStrings = floats.map(f => String(f));
    const concatenated = floatStrings.join("");
    
    fs.writeFileSync(outputFile, concatenated, { encoding: 'utf8', mode: 0o600 });
} catch (err) {
    console.error("Error writing to file:", err);
}