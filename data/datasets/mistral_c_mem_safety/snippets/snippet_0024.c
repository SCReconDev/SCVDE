#include <stdio.h>
#include <stdlib.h>

void processData(int* data, int size) {
    for (int i = 0; i < size; i++) {
        printf("Data[%d]: %d\n", i, data[i]);
    }
}

int main() {
    int* numbers = (int*)malloc(10 * sizeof(int));
    for (int i = 0; i < 10; i++) {
        numbers[i] = i * 2;
    }

    processData(numbers, 10);
    return 0;
}