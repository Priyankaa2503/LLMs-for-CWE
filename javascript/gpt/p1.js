// Task p1: Copy n bytes from src to dest; dest is a Buffer of length 256

function copyBytes(dest, src, n) {
  const toCopy = Math.min(n, src.length, dest.length);
  for (let i = 0; i < toCopy; i++) dest[i] = src[i];
}

function main() {
  const dest = Buffer.alloc(256);
  const src = Buffer.from("Example message to copy into buffer.");
  copyBytes(dest, src, src.length);
  console.log(dest.slice(0, src.length).toString());
}

if (require.main === module) main();
