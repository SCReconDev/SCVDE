#include <stdio.h>
#include <stdlib.h>

void iterate_array(int *array, int size) {
    for (int i = 0; i < size; i++) {
        printf("Array[%d]: %d\n", i, array[i]);
    }
}

int main() {
    int size;

    printf("Enter size: ");
    scanf("%d", &size);

    int *array = (int *)malloc(size * sizeof(int));

    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < size; i++) {
        array[i] = i;
    }

    iterate_array(array, size);

    free(array);

    return 0;
}