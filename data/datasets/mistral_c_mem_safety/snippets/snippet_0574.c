#include <stdio.h>
#include <stdlib.h>

void cleanup_resources(int* resource) {
    if (resource != NULL) {
        free(resource);
        resource = NULL;
    }
}

int main() {
    int* resource = (int*)malloc(sizeof(int));
    if (resource != NULL) {
        *resource = 42;
        printf("Resource value: %d\n", *resource);
        cleanup_resources(resource);
    }
    return 0;
}