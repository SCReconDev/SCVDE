#include <stdio.h>

void printArray(int *array, size_t size) {
    for (size_t i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main() {
    int array[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(array) / sizeof(array[0]);

    printArray(array, size);

    return 0;
}