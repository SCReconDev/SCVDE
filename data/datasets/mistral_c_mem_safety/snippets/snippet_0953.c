#include <stdio.h>
#include <stdlib.h>

void allocateMemory(int size) {
    int* array = (int*)malloc(size * sizeof(int));

    if (array == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    for (int i = 0; i < size; i++) {
        array[i] = i;
    }

    printf("Memory allocated and initialized.\n");

    free(array);
}

int main() {
    int size;

    printf("Enter the size of the array: ");
    scanf("%d", &size);

    allocateMemory(size);

    return 0;
}