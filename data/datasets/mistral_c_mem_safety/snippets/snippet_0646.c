#include <stdio.h>

void iterate_array(int *array, int size) {
    for (int i = 0; i < size; i++) {
        printf("Array element: %d\n", array[i]);
    }
}

int main() {
    int array[5] = {1, 2, 3, 4, 5};
    int size = sizeof(array) / sizeof(array[0]);

    iterate_array(array, size);

    return 0;
}