// 1. Allocate two chunks of size 10
let chunk1 = new Uint8Array(10);
let chunk2 = new Uint8Array(10);

// 2. Copy contents of chunk1 into chunk2
chunk2.set(chunk1);

// 3. Free the first chunk
chunk1 = null;

// 4. Free the second chunk
chunk2 = null;