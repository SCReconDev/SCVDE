#include <stdio.h>
#include <stdlib.h>

int* allocate_memory(int size) {
    int *ptr = malloc(size * sizeof(int));
    return ptr;
}

int main() {
    int *array = allocate_memory(10);
    for (int i = 0; i < 10; i++) {
        array[i] = i;
    }
    printf("Array elements: ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    return 0;
}