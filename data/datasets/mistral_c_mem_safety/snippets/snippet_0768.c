#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;
    size_t size;
} Resource;

void release_resource(Resource* resource) {
    if (resource->data != NULL) {
        free(resource->data);
        resource->data = NULL;
    }
}

void use_resource(Resource* resource) {
    if (resource->data == NULL) {
        printf("Resource not initialized\n");
        return;
    }

    for (size_t i = 0; i < resource->size; i++) {
        printf("Resource data at index %zu: %d\n", i, resource->data[i]);
    }
}

int main() {
    Resource resource;
    resource.size = 5;
    resource.data = (int*)malloc(resource.size * sizeof(int));

    if (resource.data == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (size_t i = 0; i < resource.size; i++) {
        resource.data[i] = i;
    }

    use_resource(&resource);
    release_resource(&resource);

    use_resource(&resource);

    return 0;
}