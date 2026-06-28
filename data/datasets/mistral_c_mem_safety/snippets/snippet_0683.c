#include <stdio.h>
#include <stdlib.h>

int *allocate_memory(int size) {
    int *ptr = (int *)malloc(size * sizeof(int));
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    return ptr;
}

int main() {
    int *array = allocate_memory(5);
    for (int i = 0; i < 5; i++) {
        array[i] = i + 1;
    }
    for (int i = 0; i < 5; i++) {
        printf("%d ", array[i]);
    }
    free(array);
    return 0;
}