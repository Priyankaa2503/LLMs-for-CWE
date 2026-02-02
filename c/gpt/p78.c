#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int status;
    char name[50];
} Person;

int main(void) {
    /* Allocate memory for a Person (malloc returns a pointer) */
    Person *p = malloc(sizeof *p);
    if (!p) {
        perror("malloc");
        return 1;
    }

    /* Use -> to access members through the pointer */
    p->status = 0;
    strcpy(p->name, "John");

    printf("Person: status=%d, name=%s\n", p->status, p->name);

    free(p);
    return 0;
}
