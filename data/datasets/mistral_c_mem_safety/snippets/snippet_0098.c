#include <stdio.h>
#include <stdlib.h>

void release_memory(int **ptr) {
    free(*ptr);
    *ptr = NULL;
}

void use_memory(int *ptr) {
    printf("Using memory: %d\n", *ptr);
}

int main() {
    int *data = (int *)malloc(sizeof(int));
    *data = 10;
    release_memory(&data);
    use_memory(data);
    return 0;
}