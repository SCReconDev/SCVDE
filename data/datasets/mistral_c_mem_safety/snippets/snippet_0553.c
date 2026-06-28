#include <stdio.h>
#include <stdlib.h>

void allocate_memory(size_t size) {
    int *ptr = (int *)malloc(size * sizeof(int));
    if (ptr != NULL) {
        printf("Memory allocated successfully.\n");
        free(ptr);
    } else {
        printf("Memory allocation failed.\n");
    }
}

int main() {
    size_t size;
    printf("Enter size: ");
    scanf("%zu", &size);
    allocate_memory(size);
    return 0;
}