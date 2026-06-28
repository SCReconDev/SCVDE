#include <stdio.h>
#include <stdlib.h>

void allocate_and_use_memory(int size) {
    int *ptr = (int *)malloc(size * sizeof(int));
    if (ptr != NULL) {
        for (int i = 0; i < size; i++) {
            ptr[i] = i;
        }
    }
}

int main() {
    int size;
    printf("Enter the size of memory to allocate: ");
    scanf("%d", &size);
    allocate_and_use_memory(size);
    return 0;
}