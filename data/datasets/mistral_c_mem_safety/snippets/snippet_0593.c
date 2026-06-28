#include <stdio.h>
#include <stdlib.h>

void allocate_memory(int size) {
    int *ptr = (int *)malloc(size * sizeof(int));
    if (ptr != NULL) {
        for (int i = 0; i < size; i++) {
            ptr[i] = i;
        }
        printf("Memory allocated and initialized\n");
        free(ptr);
    } else {
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