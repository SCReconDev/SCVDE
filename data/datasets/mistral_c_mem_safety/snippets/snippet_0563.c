#include <stdio.h>
#include <stdlib.h>

int* allocate_memory(int size) {
    int* ptr = (int*)malloc(size * sizeof(int));
    if (ptr == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    return ptr;
}

int main() {
    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);
    int* array = allocate_memory(size);
    if (array != NULL) {
        for (int i = 0; i < size; i++) {
            array[i] = i;
        }
        for (int i = 0; i < size; i++) {
            printf("%d ", array[i]);
        }
        printf("\n");
        free(array);
    }
    return 0;
}