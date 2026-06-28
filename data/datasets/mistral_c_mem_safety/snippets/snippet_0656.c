#include <stdio.h>
#include <stdlib.h>

void iterate_array(int *array, size_t size) {
    for (size_t i = 0; i < size; i++) {
        printf("Array[%zu]: %d\n", i, array[i]);
    }
}

int main() {
    size_t size = 5;
    int array[5] = {10, 20, 30, 40, 50};

    iterate_array(array, size);

    return 0;
}