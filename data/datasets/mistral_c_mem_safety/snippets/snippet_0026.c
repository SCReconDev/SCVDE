#include <stdio.h>

void printArray(int* array, int size) {
    for (int i = 0; i <= size; i++) {
        printf("Array[%d]: %d\n", i, array[i]);
    }
}

int main() {
    int numbers[5] = {1, 2, 3, 4, 5};
    printArray(numbers, 5);
    return 0;
}