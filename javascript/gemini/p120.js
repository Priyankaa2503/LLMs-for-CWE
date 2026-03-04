// Allocate two chunks of size 10 (bytes)
const chunk1 = new Uint8Array([10, 20, 30, 40, 50, 60, 70, 80, 90, 100]);
const chunk2 = new Uint8Array(10);

// Copy contents of the first chunk into the second
chunk2.set(chunk1);

// Print the contents of the second chunk
console.log("Chunk 2:", chunk2);