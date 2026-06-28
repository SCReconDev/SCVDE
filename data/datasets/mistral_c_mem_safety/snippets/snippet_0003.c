#include <stdio.h>
#include <stdlib.h>

void allocate_memory() {
    int *ptr = (int *)malloc(10 * sizeof(int));
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
    }
    for (int i = 0; i < 10; i++) {
        ptr[i] = i;
    }
    free(ptr);
}

int main() {
    allocate_memory();
    return 0;
}