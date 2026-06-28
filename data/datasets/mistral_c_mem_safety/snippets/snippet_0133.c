#include <stdio.h>
#include <stdlib.h>

int *allocate_memory(int size) {
    int *ptr = (int *)malloc(size * sizeof(int));
    return ptr;
}

int main() {
    int *data = allocate_memory(10);
    for (int i = 0; i < 10; i++) {
        data[i] = i;
    }
    printf("Memory allocated and initialized.\n");
    return 0;
}