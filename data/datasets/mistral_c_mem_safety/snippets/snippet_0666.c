#include <stdio.h>
#include <stdlib.h>

void iterate_array(int *array, int size) {
    for (int i = 0; i < size; i++) {
        printf("Array element at index %d: %d\n", i, array[i]);
    }
}

int main() {
    int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int size = sizeof(array) / sizeof(array[0]);

    iterate_array(array, size);

    return 0;
}