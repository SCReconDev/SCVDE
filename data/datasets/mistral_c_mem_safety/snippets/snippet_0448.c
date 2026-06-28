#include <stdio.h>
#include <stdlib.h>

void release_memory(int *ptr) {
    free(ptr);
    printf("Memory released\n");
}

int main() {
    int *data_ptr = (int *)malloc(sizeof(int));
    *data_ptr = 42;
    release_memory(data_ptr);
    printf("Using released memory: %d\n", *data_ptr);
    return 0;
}