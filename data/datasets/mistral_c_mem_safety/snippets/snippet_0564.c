#include <stdio.h>
#include <stdlib.h>

void cleanup_memory(int** ptr) {
    if (*ptr != NULL) {
        free(*ptr);
        *ptr = NULL;
    }
}

int main() {
    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);
    int* array = (int*)malloc(size * sizeof(int));
    if (array != NULL) {
        for (int i = 0; i < size; i++) {
            array[i] = i;
        }
        for (int i = 0; i < size; i++) {
            printf("%d ", array[i]);
        }
        printf("\n");
        cleanup_memory(&array);
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}