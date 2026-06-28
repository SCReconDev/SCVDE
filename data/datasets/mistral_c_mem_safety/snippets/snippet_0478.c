#include <stdio.h>
#include <stdlib.h>

void release_and_reuse(int size) {
    int *ptr = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        ptr[i] = i;
    }
    free(ptr);
    printf("Value after free: %d\n", ptr[0]);
}

int main() {
    release_and_reuse(10);
    return 0;
}