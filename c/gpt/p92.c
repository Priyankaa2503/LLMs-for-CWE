#include <stdio.h>
#include <stdlib.h>

/* p92 C: simple program showing use of openssl would be recommended, but here we just print a placeholder. */
int main(int argc, char **argv) {
    if (argc<2) { printf("Usage: %s <password>\n", argv[0]); return 1; }
    printf("This C example should use a proper PBKDF2 implementation (e.g. via OpenSSL).\n");
    return 0;
}
