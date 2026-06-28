#include <stdio.h>
#include <stdlib.h>

void print_array(int *array, size_t size) {
    for (size_t i = 0; i < size; i++) {
        printf("Array[%zu]: %d\n", i, array[i]);
    }
}

int main() {
    size_t size;
    printf("Enter size: ");
    scanf("%zu", &size);

    int *array = (int *)malloc(size * sizeof(int));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (size_t i = 0; i < size; i++) {
        array[i] = i * 3;
    }

    print_array(array, size);
    free(array);

    return 0;
}