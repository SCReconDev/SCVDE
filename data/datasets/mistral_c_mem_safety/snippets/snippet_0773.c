#include <stdio.h>
#include <stdlib.h>

void allocate_memory(size_t size) {
    void* ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    printf("Memory allocated successfully\n");
    free(ptr);
}

int main() {
    allocate_memory(1024);
    return 0;
}