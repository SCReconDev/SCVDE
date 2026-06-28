#include <stdio.h>

void dereference_pointer(int* ptr) {
    if (ptr != NULL) {
        printf("Value: %d\n", *ptr);
    } else {
        printf("Null pointer\n");
    }
}

int main() {
    int value = 42;
    int* ptr = &value;
    dereference_pointer(ptr);
    return 0;
}