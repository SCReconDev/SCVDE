#include <stdio.h>
#include <stdlib.h>

void process_pointer(int *ptr) {
    if (ptr != NULL) {
        printf("Pointer value: %d\n", *ptr);
    } else {
        printf("Null pointer\n");
    }
}

int main() {
    int value = 42;
    int *ptr = &value;
    process_pointer(ptr);
    process_pointer(NULL);
    return 0;
}