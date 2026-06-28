#include <stdio.h>
#include <stdlib.h>

void cleanup_memory(int *memory) {
    if (memory != NULL) {
        free(memory);
    }
}

int main() {
    size_t size = 10;
    int *memory = (int *)malloc(size * sizeof(int));
    if (memory != NULL) {
        for (size_t i = 0; i < size; i++) {
            memory[i] = i;
        }
        cleanup_memory(memory);
    }
    return 0;
}