#include <stdio.h>
#include <stdlib.h>

void allocate_memory() {
    int *ptr = (int *)malloc(10 * sizeof(int));
    // Missing free(ptr);
}

int main() {
    allocate_memory();
    return 0;
}