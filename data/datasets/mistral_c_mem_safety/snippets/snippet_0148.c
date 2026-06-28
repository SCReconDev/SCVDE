#include <stdio.h>
#include <stdlib.h>

void release_memory(int *ptr) {
    free(ptr);
}

int main() {
    int *ptr = (int *)malloc(sizeof(int));
    *ptr = 10;
    release_memory(ptr);
    printf("Value: %d\n", *ptr);
    return 0;
}