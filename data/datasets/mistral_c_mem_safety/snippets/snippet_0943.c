#include <stdio.h>
#include <stdlib.h>

void *safe_allocate(size_t size) {
    void *ptr = malloc(size);

    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    return ptr;
}

int main() {
    size_t size = 1024;
    void *memory = safe_allocate(size);
    printf("Allocated memory of size %zu\n", size);
    free(memory);
    return 0;
}