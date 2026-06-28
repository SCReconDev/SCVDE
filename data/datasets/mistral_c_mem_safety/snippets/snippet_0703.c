#include <stdio.h>
#include <stdlib.h>

void allocateMemory(int size) {
    int *ptr = (int *)malloc(size * sizeof(int));
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    for (int i = 0; i < size; i++) {
        ptr[i] = i;
    }
    for (int i = 0; i < size; i++) {
        printf("%d ", ptr[i]);
    }
    printf("\n");
    free(ptr);
}

int main() {
    int size;
    printf("Enter size: ");
    scanf("%d", &size);
    allocateMemory(size);
    return 0;
}