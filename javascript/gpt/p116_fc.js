// JavaScript (Node.js): list current directory contents using fs.promises.readdir with checked errors.
"use strict";

const fs = require("node:fs/promises");

async function main() {
  try {
    const entries = await fs.readdir(".", { withFileTypes: false });
    for (const name of entries) {
      process.stdout.write(String(name) + "\n");
    }
  } catch (err) {
    process.stderr.write(`Error listing directory: ${err instanceof Error ? err.message : String(err)}\n`);
    process.exitCode = 1;
  }
}

main();