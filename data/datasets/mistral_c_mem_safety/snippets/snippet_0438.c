#include <stdio.h>
#include <stdlib.h>

void free_memory(int *ptr) {
    free(ptr);
}

int main() {
    int *ptr = (int *)malloc(sizeof(int));
    *ptr = 42;
    free_memory(ptr);
    printf("Value after free: %d\n", *ptr);
    return 0;
}