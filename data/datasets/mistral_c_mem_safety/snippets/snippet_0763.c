#include <stdio.h>
#include <stdlib.h>

void allocate_memory(size_t size) {
    int* buffer = (int*)malloc(size * sizeof(int));

    if (buffer == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    for (size_t i = 0; i < size; i++) {
        buffer[i] = i;
    }

    printf("Memory allocated and initialized\n");

    free(buffer);
}

int main() {
    size_t size;
    printf("Enter size: ");
    scanf("%zu", &size);

    allocate_memory(size);

    return 0;
}