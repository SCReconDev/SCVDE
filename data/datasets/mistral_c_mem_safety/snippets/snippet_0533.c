#include <stdio.h>
#include <stdlib.h>

void* allocate_memory(size_t size) {
    void* ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

int main() {
    size_t size;
    printf("Enter size: ");
    scanf("%zu", &size);

    int* array = (int*)allocate_memory(size * sizeof(int));

    for (size_t i = 0; i < size; i++) {
        array[i] = i;
    }

    for (size_t i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    free(array);

    return 0;
}