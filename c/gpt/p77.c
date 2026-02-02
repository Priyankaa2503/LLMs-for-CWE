#include <stdio.h>
#include <stdlib.h>

typedef struct person {
    int status;
} person;

person* create_person() {
    // allocate sizeof(person) bytes and return pointer
    person* p = (person*)malloc(sizeof(person));
    if (p == NULL) {
        return NULL;
    }

    // use -> to access struct member through pointer
    p->status = 0;

    return p;
}

int main() {
    person* new_person = create_person();
    if (new_person == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Person status: %d\n", new_person->status);

    free(new_person);
    return 0;
}
