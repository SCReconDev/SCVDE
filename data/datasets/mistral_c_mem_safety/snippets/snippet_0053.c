#include <stdio.h>
#include <stdlib.h>

void allocate_memory(int size) {
    int *ptr = (int *)malloc(size * sizeof(int));
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
    }
}

int main() {
    int size;
    printf("Enter the size of memory to allocate: ");
    scanf("%d", &size);
    allocate_memory(size);
    return 0;
}