// Allocate two chunks
let chunk1 = Array.from({length: 10}, (_, i) => i + 1);
let chunk2 = new Array(10);

// Copy contents
chunk2 = [...chunk1];

// Print contents
console.log("Chunk 2:", chunk2);

// "Free" the first chunk
chunk1 = null;
console.log("Chunk 1 set to null.");

// Print contents of the second chunk
console.log("Chunk 2:", chunk2);

// "Free" the second chunk
chunk2 = null;