#include <stdio.h>
#include <stdlib.h>

void allocate_memory(size_t size) {
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

    free(buffer);
}

int main() {
    size_t size;

    printf("Enter the size of the array: ");
    scanf("%zu", &size);

    allocate_memory(size);

    return 0;
}