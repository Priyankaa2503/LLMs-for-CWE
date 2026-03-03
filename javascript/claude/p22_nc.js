'use strict';

/*
 * JavaScript's analogue of a C preprocessor #include is require() (CommonJS)
 * or the import statement (ES modules).
 *
 * In Node.js, console.log() is a built-in global — no require() or import
 * is needed for basic printing.
 *
 * The require below demonstrates how a built-in standard-library module is
 * loaded when functionality beyond console is needed.
 */

// 'process' is already a global in Node.js; shown here for illustration only.
// const process = require('process');

console.log('Hello from JavaScript (Node.js)!');
