const fs = require('fs');
const path = require('path');
const crypto = require('crypto');

const baseDir = '/tmp/secure_storage';
const filePath = path.join(baseDir, 'output.txt');

function generateSecureFloats() {
    return Array.from({ length: 3 }, () => crypto.randomBytes(8).readUInt32BE(0) / 0xFFFFFFFF);
}

try {
    if (!fs.existsSync(baseDir)) {
        fs.mkdirSync(baseDir, { mode: 0o700 });
    }
    
    const data = generateSecureFloats().map(String).join('');
    fs.writeFileSync(filePath, data, { mode: 0o600 });
} catch (err) {
    process.exit(1);
}