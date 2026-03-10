// JavaScript (non-crypto RNG via Math.random)
function floatToString(x) {
  // Explicit, fixed formatting (not user-controlled)
  return x.toFixed(6);
}

const a = Math.random();
const b = Math.random();
const c = Math.random();

if (!(Number.isFinite(a) && Number.isFinite(b) && Number.isFinite(c))) {
  throw new Error("Non-finite float generated");
}

const str_a = floatToString(a);
const str_b = floatToString(b);
const str_c = floatToString(c);