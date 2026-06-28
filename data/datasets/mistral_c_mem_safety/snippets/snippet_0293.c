#include <stdio.h>
#include <stdlib.h>

void allocate_memory(int size) {
    int *ptr = (int *)malloc(size * sizeof(int));
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
    }
}

int main() {
    allocate_memory(10000000000);
    return 0;
}