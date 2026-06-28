#include <stdio.h>
#include <stdlib.h>

int allocate_memory(int size) {
    int *ptr = (int *)malloc(size * sizeof(int));
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        return -1;
    }
    for (int i = 0; i < size; i++) {
        ptr[i] = i;
    }
    for (int i = 0; i < size; i++) {
        printf("%d ", ptr[i]);
    }
    free(ptr);
    return 0;
}

int main() {
    int size;
    printf("Enter the size: ");
    scanf("%d", &size);
    allocate_memory(size);
    return 0;
}