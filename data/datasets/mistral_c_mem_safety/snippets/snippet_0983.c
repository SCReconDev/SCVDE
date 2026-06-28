#include <stdio.h>
#include <stdlib.h>

void *safe_alloc(size_t size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

int main() {
    size_t size = 100;
    int *array = (int *)safe_alloc(size * sizeof(int));
    for (size_t i = 0; i < size; i++) {
        array[i] = i;
    }
    printf("Allocation successful\n");
    free(array);
    return 0;
}