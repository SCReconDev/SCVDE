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
    dereference_pointer(&value);
    return 0;
}