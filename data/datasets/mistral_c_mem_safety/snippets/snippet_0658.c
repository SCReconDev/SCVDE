#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Resource;

void release_resource(Resource *resource) {
    if (resource->data != NULL) {
        free(resource->data);
        resource->data = NULL;
        resource->size = 0;
    }
}

int main() {
    Resource resource;
    resource.size = 10;
    resource.data = (int *)malloc(resource.size * sizeof(int));

    if (resource.data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < resource.size; i++) {
        resource.data[i] = i * 3;
    }

    release_resource(&resource);

    if (resource.data == NULL) {
        printf("Resource released successfully\n");
    }

    return 0;
}