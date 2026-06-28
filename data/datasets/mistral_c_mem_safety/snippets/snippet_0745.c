#include <stdio.h>
#include <stdlib.h>

void dereference_pointer(int *ptr) {
    if (ptr != NULL) {
        printf("Value: %d\n", *ptr);
    } else {
        printf("Null pointer\n");
    }
}

int main() {
    int *ptr = (int *)malloc(sizeof(int));
    if (ptr != NULL) {
        *ptr = 42;
        dereference_pointer(ptr);
        free(ptr);
    } else {
        printf("Memory allocation failed\n");
    }
    return 0;
}