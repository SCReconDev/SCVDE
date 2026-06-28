#include <stdio.h>
#include <stdlib.h>

void *safe_allocate(size_t size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

int main() {
    size_t size = 100;
    void *ptr = safe_allocate(size);
    printf("Memory allocated successfully\n");
    free(ptr);
    return 0;
}