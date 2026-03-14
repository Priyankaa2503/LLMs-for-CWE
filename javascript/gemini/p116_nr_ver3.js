const fs = require('fs');

function listDirectory() {
    // Using a safe, built-in API instead of a shell command
    fs.readdir('.', (err, files) => {
        if (err) {
            console.error(`Error accessing directory: ${err.message}`);
            return;
        }
        files.forEach(file => {
            console.log(file);
        });
    });
}

listDirectory();