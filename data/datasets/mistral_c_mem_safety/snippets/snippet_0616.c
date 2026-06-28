#include <stdio.h>

void safeIterationLogic(int *array, size_t size) {
    for (size_t i = 0; i < size; i++) {
        printf("Value at index %zu: %d\n", i, array[i]);
    }
}

int main() {
    int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    size_t size = sizeof(array) / sizeof(array[0]);
    safeIterationLogic(array, size);
    return 0;
}