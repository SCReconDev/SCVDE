#include <stdio.h>
#include <stdlib.h>

int* allocateMemory(int size) {
    int* ptr = (int*)malloc(size * sizeof(int));
    return ptr;
}

int main() {
    int* numbers = allocateMemory(10);
    for (int i = 0; i < 10; i++) {
        numbers[i] = i * 5;
    }

    printf("Memory allocated successfully.\n");
    return 0;
}