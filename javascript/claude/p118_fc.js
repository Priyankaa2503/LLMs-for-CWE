// Node.js: Secure random floats to file
const crypto = require('crypto');
const fs = require('fs');
const path = require('path');

function writeRandomFloats() {
    // Fixed output directory with constraints
    const outputDir = '/tmp/secure_output';
    if (!fs.existsSync(outputDir)) {
        fs.mkdirSync(outputDir, { mode: 0o700, recursive: true });
    }
    
    // Fixed filename (no user input)
    const filepath = path.join(outputDir, 'random_floats.txt');
    
    try {
        // Generate 3 cryptographically-secure random floats
        const floats = [];
        for (let i = 0; i < 3; i++) {
            const randomBytes = crypto.randomBytes(8);
            const randomFloat = randomBytes.readDoubleBE(0) % 1.0;
            floats.push(Math.abs(randomFloat));
        }
        
        // Convert to strings with explicit safe formatting
        const formatted = floats.map(f => f.toFixed(17).replace(/0+$/, ''));
        const delimiter = '|';
        const result = formatted.join(delimiter);
        
        // Write with safe file handling
        fs.writeFileSync(filepath, result, { mode: 0o600 });
        console.log(`Success: ${result}`);
    } catch (error) {
        if (error.code === 'EACCES' || error.code === 'ENOENT') {
            console.error(`File error: ${error.message}`);
        } else {
            console.error(`Unexpected error: ${error.message}`);
        }
    }
}

writeRandomFloats();