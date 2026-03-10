// JavaScript (Node.js)
const fs = require('fs');

// Safe API approach - no shell execution
fs.readdir('.', (err, files) => {
    if (err) {
        console.error('Error reading directory:', err);
        return;
    }
    files.forEach(file => {
        console.log(file);
    });
});

// Synchronous alternative
const files = fs.readdirSync('.');
files.forEach(file => {
    console.log(file);
});