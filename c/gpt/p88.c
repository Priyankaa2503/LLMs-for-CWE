#include <stdio.h>
#include <string.h>

/* C placeholder for p88: read YAML-like payload from stdin and compute price */
int main(void) {
    char buf[8192];
    size_t n = fread(buf,1,sizeof(buf)-1,stdin);
    buf[n]='\0';
    char *pc = strstr(buf, "product_code:");
    char *q = strstr(buf, "quantity:");
    if (!pc || !q) {
        printf("Content-Type: application/json\n\n{\"error\": \"missing fields\"}\n");
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
    printf("Content-Type: text/plain\n\n%f\n", total);
    return 0;
}
