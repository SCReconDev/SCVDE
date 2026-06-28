#include <stdio.h>
#include <stdlib.h>

void release_resource(int *resource) {
    free(resource);
}

int main() {
    int *resource = malloc(sizeof(int));
    *resource = 100;
    printf("Resource value: %d\n", *resource);
    release_resource(resource);
    printf("Resource value after release: %d\n", *resource);
    return 0;
}