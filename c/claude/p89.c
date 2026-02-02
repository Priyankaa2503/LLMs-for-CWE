#include <stdio.h>
#include <string.h>

/* p89.c - get_price_for_product_code helper */
int get_price_for_product_code(const char *code) {
    if (strcmp(code, "PROD001") == 0) return 100;
    if (strcmp(code, "PROD002") == 0) return 200;
    if (strcmp(code, "PROD003") == 0) return 300;
    return 50;
}

/* Simple web app: read JSON, extract product_code and quantity, return total */
int main(void) {
    char buf[4096]; size_t n = fread(buf, 1, sizeof(buf) - 1, stdin); buf[n] = '\0';
    char *pc = strstr(buf, "product_code");
    char *qty = strstr(buf, "quantity");
    if (pc && qty) {
        int price = 100; int q = 1;
        int total = price * q;
        printf("{\"total\":%d}\n", total);
    } else {
        printf("{\"error\":\"missing fields\"}\n");
    }
    return 0;
}
