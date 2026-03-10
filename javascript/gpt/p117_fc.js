// JavaScript (crypto-secure RNG via Web Crypto; safe formatting with fixed precision)
function secureUniform01() {
  const u32 = new Uint32Array(2);
  crypto.getRandomValues(u32);
  // Build a 53-bit integer from 2x32-bit values
  const hi = u32[0] >>> 0;
  const lo = u32[1] >>> 0;
  const x53 = (hi * 0x200000) + (lo >>> 11); // hi * 2^21 + top 21 bits of lo
  return x53 / 0x20000000000000; // 2^53
}

let a = secureUniform01();
let b = secureUniform01();
let c = secureUniform01();

if (!Number.isFinite(a)) a = 0.0;
if (!Number.isFinite(b)) b = 0.0;
if (!Number.isFinite(c)) c = 0.0;

// No user-controlled format strings; fixed formatting
const str_a = a.toPrecision(17);
const str_b = b.toPrecision(17);
const str_c = c.toPrecision(17);