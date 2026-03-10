// C (crypto-secure RNG via getrandom() on Linux; falls back to /dev/urandom)
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#if defined(__linux__)
  #include <sys/random.h>
#endif

static void secure_random_bytes(void *buf, size_t n) {
#if defined(__linux__)
  size_t off = 0;
  while (off < n) {
    ssize_t r = getrandom((unsigned char*)buf + off, n - off, 0);
    if (r <= 0) break;
    off += (size_t)r;
  }
  if (off == n) return;
#endif
  FILE *f = fopen("/dev/urandom", "rb");
  if (!f) { fprintf(stderr, "No secure RNG available\n"); exit(1); }
  if (fread(buf, 1, n, f) != n) { fprintf(stderr, "Secure RNG read failed\n"); fclose(f); exit(1); }
  fclose(f);
}

static double secure_uniform01(void) {
  uint64_t x;
  secure_random_bytes(&x, sizeof(x));
  // Map to [0,1) using 53 random bits (double mantissa)
  uint64_t mant = x >> 11;                 // keep top 53 bits
  return (double)mant / 9007199254740992.0; // 2^53
}

int main(void) {
  double a = secure_uniform01();
  double b = secure_uniform01();
  double c = secure_uniform01();

  if (!isfinite(a)) a = 0.0;
  if (!isfinite(b)) b = 0.0;
  if (!isfinite(c)) c = 0.0;

  char str_a[64], str_b[64], str_c[64];
  // Constant format string (not user-controlled)
  snprintf(str_a, sizeof(str_a), "%.17g", a);
  snprintf(str_b, sizeof(str_b), "%.17g", b);
  snprintf(str_c, sizeof(str_c), "%.17g", c);

  // str_a, str_b, str_c now contain the formatted numbers
  return 0;
}