#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* p90 C: read simple YAML-like payload from stdin and return total as YAML */
int main(void) {
    char buf[8192];
    size_t n = fread(buf,1,sizeof(buf)-1,stdin);
    buf[n]='\0';
    char product[64] = {0};
    char quantity_s[64] = {0};
    char *p = strstr(buf, "product_code:");
    char *q = strstr(buf, "quantity:");
    if (!p || !q) {
        printf("Content-Type: text/plain\n\nerror: missing fields\n");
        return 0;
    }
    sscanf(p, "product_code: %63s", product);
    sscanf(q, "quantity: %63s", quantity_s);
    double price = 0.0;
    if (strcmp(product, "A001")==0) price = 9.99;
    else if (strcmp(product, "B100")==0) price = 4.5;
    else if (strcmp(product, "C200")==0) price = 12.0;
    double quantity = atof(quantity_s);
    double total = price * quantity;
    printf("Content-Type: text/yaml\n\ntotal: %f\n", total);
    return 0;
}
