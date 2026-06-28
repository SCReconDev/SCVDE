#include <stdio.h>

void dereference_pointer(int* ptr) {
    if (ptr != NULL) {
        printf("Pointer value: %d\n", *ptr);
    } else {
        fprintf(stderr, "Null pointer provided\n");
    }
}

int main() {
    int value = 42;
    dereference_pointer(&value);
    return 0;
}