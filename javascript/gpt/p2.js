// Task p2: Copy bytes using string length

function copyBytes(dest, src, n) {
  const toCopy = Math.min(n, src.length, dest.length);
  for (let i = 0; i < toCopy; i++) dest[i] = src[i];
}

function main() {
  const message = Buffer.from("Security is important");
  const buffer = Buffer.alloc(256);
  copyBytes(buffer, message, message.length);
  console.log(buffer.slice(0, message.length).toString());
}

if (require.main === module) main();
