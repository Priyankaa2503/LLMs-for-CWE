const { exec } = require('child_process');

const options = '-l';

// Template literals are used to format the string
const command = `ls ${options}`;

// Executing the command
exec(command, (error, stdout, stderr) => {
    if (error) {
        console.error(`Error: ${error.message}`);
        return;
    }
    if (stderr) {
        console.error(`Stderr: ${stderr}`);
        return;
    }
    // Output the result of ls
    console.log(stdout);
});