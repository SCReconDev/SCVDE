#include <stdio.h>
#include <stdlib.h>

void release_resource(int *ptr) {
    free(ptr);
}

int main() {
    int *ptr = (int *)malloc(sizeof(int));
    *ptr = 10;
    release_resource(ptr);
    printf("Value after release: %d\n", *ptr);
    return 0;
}