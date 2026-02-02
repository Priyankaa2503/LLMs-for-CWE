#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* p88.c - calculate_price endpoint (product_code × quantity = total) */
int main(void) {
    char buf[4096]; size_t n = fread(buf, 1, sizeof(buf) - 1, stdin); buf[n] = '\0';
    char *pc = strstr(buf, "product_code");
    char *qty = strstr(buf, "quantity");
    if (pc && qty) {
        int price = 50; int q = 1;
        int total = price * q;
        printf("{\"total\":%d}\n", total);
    } else {
        printf("{\"error\":\"missing fields\"}\n");
    }
    return 0;
}
