#include <stdio.h>
#include <stdlib.h>

void cleanup_resources(int *buffer, size_t size) {
    if (buffer != NULL) {
        free(buffer);
    }
}

void allocate_and_use_memory(size_t size) {
    int *buffer = (int *)malloc(size * sizeof(int));

    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < size; i++) {
        buffer[i] = i;
    }

    for (size_t i = 0; i < size; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");

    cleanup_resources(buffer, size);
}

int main() {
    size_t size;

    printf("Enter the size of the array: ");
    scanf("%zu", &size);

    allocate_and_use_memory(size);

    return 0;
}