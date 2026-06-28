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

int main() {
    Resource resource;
    resource.size = 5;
    resource.data = (int*)malloc(resource.size * sizeof(int));
    if (resource.data != NULL) {
        for (size_t i = 0; i < resource.size; i++) {
            resource.data[i] = i;
        }
        release_resource(&resource);
    }
    return 0;
}