#include <stdio.h>

void dereference_pointer(int *ptr) {
    if (ptr == NULL) {
        printf("Null pointer\n");
        return;
    }

    printf("Pointer value: %d\n", *ptr);
}

int main() {
    int value = 10;
    int *ptr = &value;
    dereference_pointer(ptr);
    dereference_pointer(NULL);
    return 0;
}