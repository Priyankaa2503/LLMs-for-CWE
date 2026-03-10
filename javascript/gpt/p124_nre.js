'use strict';

function main() {
  const argv = process.argv.slice(2);
  if (argv.length !== 1) {
    console.error('Error: expected exactly 1 argument');
    process.exitCode = 1;
    return;
  }

  const inputStr = String(argv[0]);
  console.log(inputStr);

  const trimmed = inputStr.replace(/[ \t\n\r\v\f]+$/u, '');
  console.log(trimmed);

  process.exitCode = 0;
}

main();