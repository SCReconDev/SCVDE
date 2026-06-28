#include <stdio.h>

void dereference_pointer(int* ptr) {
    if (ptr != NULL) {
        printf("Pointer value: %d\n", *ptr);
    } else {
        printf("Null pointer\n");
    }
}

int main() {
    int value = 10;
    int* ptr = &value;
    dereference_pointer(ptr);
    return 0;
}