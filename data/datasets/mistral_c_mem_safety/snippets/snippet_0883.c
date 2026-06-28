#include <stdio.h>
#include <stdlib.h>

void allocate_memory() {
    int *ptr = (int *)malloc(sizeof(int));

    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    *ptr = 42;
    printf("Allocated value: %d\n", *ptr);

    free(ptr);
}

int main() {
    allocate_memory();
    return 0;
}