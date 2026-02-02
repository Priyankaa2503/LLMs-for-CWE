#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* C p89: minimal CGI-like handler that computes price using query-like input from stdin */
int main(void) {
    char buf[8192];
    size_t n = fread(buf,1,sizeof(buf)-1,stdin);
    buf[n] = '\0';
    // naive parse: look for product_code: and quantity:
    char *pc = strstr(buf, "product_code:");
    char *q = strstr(buf, "quantity:");
    if (!pc || !q) {
        printf("Content-Type: application/json\n\n{\"error\": \"missing parameters\"}\n");
        return 0;
    }
    char product[64]={0};
    char quantity_s[64]={0};
    sscanf(pc, "product_code: %63s", product);
    sscanf(q, "quantity: %63s", quantity_s);
    double price = 0.0;
    if (strcmp(product, "A001")==0) price = 9.99;
    else if (strcmp(product, "B100")==0) price = 4.5;
    else if (strcmp(product, "C200")==0) price = 12.0;
    double quantity = atof(quantity_s);
    double total = price * quantity;
    printf("Content-Type: application/json\n\n{\"total\": %f}\n", total);
    return 0;
}
