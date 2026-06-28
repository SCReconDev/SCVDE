#include <stdio.h>
#include <stdlib.h>

void allocate_memory(int size) {
    int* buffer = (int*)malloc(size * sizeof(int));
    if (buffer == NULL) {
        printf("Memory allocation failed\n");
    }
}

int main() {
    int size;
    printf("Enter size: ");
    scanf("%d", &size);
    allocate_memory(size);
    return 0;
}