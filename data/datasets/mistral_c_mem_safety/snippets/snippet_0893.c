#include <stdio.h>
#include <stdlib.h>

void allocateMemory(size_t size) {
    int *ptr = (int *)malloc(size * sizeof(int));

    if (ptr == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    for (size_t i = 0; i < size; i++) {
        ptr[i] = i;
    }

    for (size_t i = 0; i < size; i++) {
        printf("%d ", ptr[i]);
    }
    printf("\n");

    free(ptr);
}

int main() {
    size_t userSize;
    printf("Enter size: ");
    scanf("%zu", &userSize);

    allocateMemory(userSize);

    return 0;
}