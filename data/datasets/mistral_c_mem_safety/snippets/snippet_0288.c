#include <stdio.h>
#include <stdlib.h>

void release_resource(int *ptr) {
    free(ptr);
    printf("Resource released\n");
}

int main() {
    int *resource = (int *)malloc(sizeof(int));
    *resource = 42;
    release_resource(resource);
    printf("Value after release: %d\n", *resource);
    return 0;
}