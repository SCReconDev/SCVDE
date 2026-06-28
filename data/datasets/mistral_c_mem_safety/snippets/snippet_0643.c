#include <stdio.h>
#include <stdlib.h>

void allocate_memory(int size) {
    int *ptr = (int *)malloc(size * sizeof(int));

    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    for (int i = 0; i < size; i++) {
        ptr[i] = i;
    }

    printf("Memory allocated and initialized\n");

    free(ptr);
}

int main() {
    int size = 10;
    allocate_memory(size);

    return 0;
}