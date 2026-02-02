#include <stdio.h>
#include <stdlib.h>

/* p78.c
   Allocate a block of memory for a struct person and set status to 0.
*/
typedef struct { int status; char name[128]; } person;

int main(void) {
    person *p = (person *)malloc(sizeof(person));
    if (!p) { perror("malloc"); return 1; }
    p->status = 0;
    printf("Allocated person with status: %d\n", p->status);
    free(p);
    return 0;
}
