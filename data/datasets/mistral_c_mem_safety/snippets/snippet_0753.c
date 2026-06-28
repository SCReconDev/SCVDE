#include <stdio.h>
#include <stdlib.h>

int* allocateArray(int size) {
    if (size <= 0) {
        printf("Invalid size.\n");
        return NULL;
    }
    int *arr = (int*)malloc(size * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
    }
    return arr;
}

int main() {
    int size;
    printf("Enter array size: ");
    scanf("%d", &size);
    int *arr = allocateArray(size);
    if (arr != NULL) {
        for (int i = 0; i < size; i++) {
            arr[i] = i + 1;
        }
        for (int i = 0; i < size; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
        free(arr);
    }
    return 0;
}