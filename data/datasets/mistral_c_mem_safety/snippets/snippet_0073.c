#include <stdio.h>
#include <stdlib.h>

void allocate_memory(int size) {
    int* ptr = (int*)malloc(size * sizeof(int));
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
    }
    for (int i = 0; i < size; i++) {
        ptr[i] = i;
    }
    printf("Memory allocated successfully\n");
}

int main() {
    int size;
    printf("Enter the size: ");
    scanf("%d", &size);
    allocate_memory(size);
    return 0;
}