#include <stdio.h>
#include <stdlib.h>

int* createArray(int size) {
    int* array = (int*)malloc(size * sizeof(int));
    return array;
}

int main() {
    int* numbers = createArray(10);
    for (int i = 0; i < 10; i++) {
        numbers[i] = i * 6;
    }

    printf("Array created.\n");
    return 0;
}