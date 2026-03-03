'use strict';

/*
 * In browser JavaScript, console.log is always available — no import needed.
 * In Node.js, core globals (console, process) are also pre-loaded.
 *
 * The two require() calls below mirror the C pattern (I/O + stdlib) and show
 * the idiomatic CommonJS mechanism for importing Node.js built-in modules.
 */
const fs   = require('fs');   /* built-in file-system module — the I/O equivalent of stdio.h   */
const path = require('path'); /* built-in path utilities — the stdlib equivalent of stdlib.h    */

/* console.log needs no import; fs and path are shown purely to illustrate require() */
console.log('Modules loaded: fs (I/O) and path (standard library path utilities).');
