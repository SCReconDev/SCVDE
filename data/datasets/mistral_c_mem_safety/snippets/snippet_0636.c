#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 10

void iterate_array(int *array, size_t size) {
    if (array == NULL) {
        fprintf(stderr, "Null array\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main() {
    int array[ARRAY_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    iterate_array(array, ARRAY_SIZE);

    return 0;
}