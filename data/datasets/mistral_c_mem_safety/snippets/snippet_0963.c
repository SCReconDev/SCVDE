#include <stdio.h>
#include <stdlib.h>

void allocate_memory(size_t size) {
    void *ptr = malloc(size);

    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    printf("Memory allocated successfully\n");
    free(ptr);
}

int main() {
    allocate_memory(100);
    return 0;
}