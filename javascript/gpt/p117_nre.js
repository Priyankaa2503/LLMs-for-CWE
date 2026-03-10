function randomFloat01() {
  // Cryptographically secure RNG via Web Crypto API.
  const u32 = new Uint32Array(2);
  crypto.getRandomValues(u32);

  // Build a 53-bit integer from two 32-bit limbs.
  const hi = u32[0] >>> 5;           // 27 bits
  const lo = u32[1] >>> 6;           // 26 bits
  const x = hi * (1 << 26) + lo;     // 53 bits (safe integer)

  const d = x / 2 ** 53;             // [0,1)
  if (!Number.isFinite(d)) throw new Error("non-finite number");
  return d;
}

function floatToStr(x) {
  if (!Number.isFinite(x)) throw new Error("non-finite number");
  return x.toFixed(6);
}

const a = randomFloat01();
const b = randomFloat01();
const c = randomFloat01();

const str_a = floatToStr(a);
const str_b = floatToStr(b);
const str_c = floatToStr(c);