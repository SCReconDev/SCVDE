#include <stdio.h>
#include <stdlib.h>

void allocate_memory(int size) {
    int *ptr = (int *)malloc(size * sizeof(int));
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    printf("Memory allocated successfully\n");
    free(ptr);
}

int main() {
    int size;
    printf("Enter size: ");
    scanf("%d", &size);
    allocate_memory(size);
    return 0;
}