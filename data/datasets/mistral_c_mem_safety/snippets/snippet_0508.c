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
        resource->size = 0;
    }
}

void use_resource(Resource* resource) {
    if (resource->data != NULL) {
        printf("Using resource\n");
    } else {
        printf("Resource not available\n");
    }
}

int main() {
    Resource resource;
    resource.data = malloc(10 * sizeof(int));
    resource.size = 10;
    if (resource.data != NULL) {
        use_resource(&resource);
        release_resource(&resource);
        use_resource(&resource);
    } else {
        printf("Memory allocation failed\n");
    }
    return 0;
}