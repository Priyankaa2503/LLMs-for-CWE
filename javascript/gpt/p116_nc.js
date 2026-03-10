// JavaScript (Node.js): list current directory without shell execution
"use strict";

const fs = require("fs/promises");

async function main() {
  const path = "."; // not user-controlled
  try {
    const entries = await fs.readdir(path, { withFileTypes: true });
    for (const ent of entries) {
      process.stdout.write(ent.name + "\n");
    }
  } catch (err) {
    process.stderr.write(`readdir('${path}') failed: ${err?.message ?? String(err)}\n`);
    process.exitCode = 1;
  }
}

main();