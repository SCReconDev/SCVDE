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

int main() {
    Resource resource;
    resource.data = malloc(100 * sizeof(int));
    resource.size = 100;
    release_resource(&resource);
    return 0;
}