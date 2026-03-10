// JavaScript (Node.js): Secure directory listing using fs.promises
const fs = require('fs').promises;
const path = require('path');

const target = process.argv[2] || '.';

(async () => {
    try {
        const entries = await fs.readdir(target, { withFileTypes: false });
        entries.forEach(entry => console.log(entry));
    } catch (error) {
        if (error.code === 'ENOENT') {
            console.error(`Error: ${target} not found`);
        } else if (error.code === 'EACCES') {
            console.error(`Error: permission denied for ${target}`);
        } else {
            console.error(`Error: ${error.message}`);
        }
        process.exit(1);
    }
})();