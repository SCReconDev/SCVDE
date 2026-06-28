#include <stdio.h>
#include <stdlib.h>

void* allocate_resource(size_t size) {
    void* resource = malloc(size);
    if (resource == NULL) {
        printf("Allocation failed\n");
        exit(1);
    }
    return resource;
}

int main() {
    size_t size = 100;
    void* resource = allocate_resource(size);
    free(resource);
    return 0;
}