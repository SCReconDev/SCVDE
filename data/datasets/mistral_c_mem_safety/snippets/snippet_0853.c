#include <stdio.h>
#include <stdlib.h>

int *allocate_memory(size_t size) {
    int *memory = (int *)malloc(size * sizeof(int));
    if (memory == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    return memory;
}

int main() {
    size_t size = 10;
    int *memory = allocate_memory(size);
    if (memory != NULL) {
        for (size_t i = 0; i < size; i++) {
            memory[i] = i;
        }
        free(memory);
    }
    return 0;
}