#include <stdio.h>
#include <stdlib.h>

void release_memory(int **ptr) {
    free(*ptr);
    *ptr = NULL;
}

int main() {
    int *ptr = (int *)malloc(10 * sizeof(int));
    release_memory(&ptr);
    printf("Value: %d\n", *ptr);
    return 0;
}