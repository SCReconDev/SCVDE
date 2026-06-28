#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Resource;

void release_resource(Resource *resource) {
    if (resource == NULL || resource->data == NULL) {
        fprintf(stderr, "Null pointer\n");
        return;
    }

    free(resource->data);
    resource->data = NULL;
    resource->size = 0;
}

int main() {
    Resource resource;
    size_t size = 10;

    resource.data = (int *)malloc(size * sizeof(int));
    if (resource.data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    resource.size = size;
    for (size_t i = 0; i < size; i++) {
        resource.data[i] = i * 4;
    }

    release_resource(&resource);

    return 0;
}