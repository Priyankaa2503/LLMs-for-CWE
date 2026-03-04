// 1. Check for exactly one argument
if (process.argv.length !== 3) {
    console.log("Error: Provide exactly one argument.");
    process.exit(1);
}

let arg = process.argv[2];

// 2. Check if it's a string
if (typeof arg !== 'string') {
    process.exit(1);
}

let charArray = arg.split('');

// 3. Trim trailing whitespace
for (let i = charArray.length - 1; i >= 0; i--) {
    if (/\s/.test(charArray[i])) {
        charArray.pop();
    } else {
        break;
    }
}

// 4. Trim newlines
for (let i = 0; i < charArray.length; i++) {
    if (charArray[i] === '\n' || charArray[i] === '\r') {
        charArray[i] = '';
    }
}

// 5. Join (JS handles the rest)
const result = charArray.join('');
console.log(`Result: '${result}'`);