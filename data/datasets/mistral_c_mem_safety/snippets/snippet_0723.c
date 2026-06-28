#include <stdio.h>
#include <stdlib.h>

int* allocate_memory(int size) {
    if (size <= 0) {
        printf("Invalid size\n");
        return NULL;
    }
    int *ptr = (int*)malloc(size * sizeof(int));
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
    }
    return ptr;
}

int main() {
    int size = 10;
    int *ptr = allocate_memory(size);
    if (ptr != NULL) {
        for (int i = 0; i < size; i++) {
            ptr[i] = i;
        }
        for (int i = 0; i < size; i++) {
            printf("%d ", ptr[i]);
        }
        printf("\n");
        free(ptr);
    }
    return 0;
}