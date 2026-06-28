#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Array;

Array* createArray(int size) {
    if (size <= 0) {
        printf("Invalid size.\n");
        return NULL;
    }
    Array *arr = (Array*)malloc(sizeof(Array));
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    arr->data = (int*)malloc(size * sizeof(int));
    if (arr->data == NULL) {
        printf("Memory allocation failed.\n");
        free(arr);
        return NULL;
    }
    arr->size = size;
    return arr;
}

void freeArray(Array *arr) {
    if (arr != NULL) {
        free(arr->data);
        free(arr);
    }
}

int main() {
    int size;
    printf("Enter array size: ");
    scanf("%d", &size);
    Array *arr = createArray(size);
    if (arr != NULL) {
        for (int i = 0; i < arr->size; i++) {
            arr->data[i] = i + 1;
        }
        for (int i = 0; i < arr->size; i++) {
            printf("%d ", arr->data[i]);
        }
        printf("\n");
        freeArray(arr);
    }
    return 0;
}