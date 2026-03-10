const fs = require("fs");

function listDir() {
    fs.readdir(".", (err, files) => {
        if (err) {
            console.error("Error listing directory:", err.message);
            process.exit(1);
        }
        files.forEach(f => console.log(f));
    });
}

listDir();