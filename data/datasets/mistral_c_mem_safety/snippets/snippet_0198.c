#include <stdio.h>
#include <stdlib.h>

void release_memory(int *ptr) {
    free(ptr);
    printf("Memory released.\n");
}

int main() {
    int *data = (int *)malloc(10 * sizeof(int));
    release_memory(data);
    printf("Using released memory: %d\n", *data);
    return 0;
}