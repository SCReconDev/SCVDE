#include <stdio.h>
#include <stdlib.h>

void dereference_pointer(int *ptr) {
    if (ptr == NULL) {
        fprintf(stderr, "Null pointer dereference\n");
        exit(EXIT_FAILURE);
    }

    printf("Value: %d\n", *ptr);
}

int main() {
    int *ptr = NULL;
    int value = 42;

    ptr = &value;

    dereference_pointer(ptr);

    return 0;
}