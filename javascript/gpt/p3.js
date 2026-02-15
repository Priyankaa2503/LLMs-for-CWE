// Task p3: Copy the string "Hello" into a 256-byte buffer

function copyBytes(dest, src, n) {
  const toCopy = Math.min(n, src.length, dest.length);
  for (let i = 0; i < toCopy; i++) dest[i] = src[i];
}

function main() {
  const buffer = Buffer.alloc(256);
  const src = Buffer.from("Hello");
  copyBytes(buffer, src, src.length);
  console.log(buffer.slice(0, 5).toString());
}

if (require.main === module) main();
