#include <stdio.h>
#include <stdlib.h>

void release_and_reuse() {
    int *ptr = (int *)malloc(10 * sizeof(int));
    free(ptr);
    *ptr = 10;
}

int main() {
    release_and_reuse();
    return 0;
}