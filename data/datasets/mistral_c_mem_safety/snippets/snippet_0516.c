#include <stdio.h>

void iterate_array(int* array, size_t size) {
    for (size_t i = 0; i < size; i++) {
        printf("Array[%zu]: %d\n", i, array[i]);
    }
}

int main() {
    int array[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(array) / sizeof(array[0]);
    iterate_array(array, size);
    return 0;
}