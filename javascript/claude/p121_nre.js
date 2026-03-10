// JavaScript
const buffer1 = Buffer.alloc(10);
const buffer2 = Buffer.alloc(10);

buffer1.write("Hello", 0, 5, 'utf8');
buffer1.copy(buffer2, 0, 0, 10);

console.log("Chunk2 contents:", buffer2.toString('utf8').trim());

buffer1 = null;

console.log("Chunk2 after nullifying buffer1:", buffer2.toString('utf8').trim());

buffer2 = null;