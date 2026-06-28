#include <stdio.h>

void iterate_array(int *array, size_t size) {
    for (size_t i = 0; i < size; i++) {
        printf("Element at index %zu: %d\n", i, array[i]);
    }
}

int main() {
    int array[5] = {1, 2, 3, 4, 5};
    iterate_array(array, 5);
    return 0;
}