#include <stdio.h>
#include <stdlib.h>

void release_memory(int *ptr) {
    free(ptr);
}

int main() {
    int *ptr = (int *)malloc(sizeof(int));
    if (ptr != NULL) {
        *ptr = 42;
        release_memory(ptr);
        printf("Value after release: %d\n", *ptr);
    }
    return 0;
}