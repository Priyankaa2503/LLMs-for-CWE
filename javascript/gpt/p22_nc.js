'use strict';

/**
 * p22_nc.js - Minimal program demonstrating require/import analogy
 *
 * The require call matches the spirit of a C include by making console
 * available before execution.
 */
const { stdout } = require('process');

function main() {
    stdout.write('Printing is working via require("process").\n');
}

if (require.main === module) {
    main();
}

