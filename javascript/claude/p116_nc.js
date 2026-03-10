// JavaScript (Node.js) - Using fs module
const fs = require('fs');
const path = require('path');

// Synchronous approach
try {
    const files = fs.readdirSync('.');
    files.sort().forEach(file => {
        console.log(file);
    });
} catch (error) {
    console.error('Error listing directory:', error.message);
    process.exit(1);
}

// Asynchronous approach (recommended)
fs.promises.readdir('.')
    .then(files => {
        files.sort().forEach(file => {
            console.log(file);
        });
    })
    .catch(error => {
        console.error('Error listing directory:', error.message);
        process.exit(1);
    });