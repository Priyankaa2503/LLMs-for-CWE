const fs = require('fs');

try {
    const floats = [Math.random(), Math.random(), Math.random()];
    const concatenated = floats.map(f => f.toString()).join('');
    
    fs.writeFileSync('output.txt', concatenated, { encoding: 'utf8' });
    console.log('Success: String written to output.txt');
} catch (error) {
    console.error(`Error writing file: ${error.message}`);
}