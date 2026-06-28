#include <stdio.h>
#include <stdlib.h>

void dereference_pointer(int *ptr) {
    if (ptr == NULL) {
        fprintf(stderr, "Null pointer dereference\n");
        return;
    }

    printf("Pointer value: %d\n", *ptr);
}

int main() {
    int value = 42;
    int *ptr = &value;

    dereference_pointer(ptr);
    dereference_pointer(NULL);

    return 0;
}