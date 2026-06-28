#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;
    size_t size;
} Resource;

void release_resource(Resource* resource) {
    if (resource != NULL && resource->data != NULL) {
        free(resource->data);
        resource->data = NULL;
        printf("Resource released successfully\n");
    } else {
        fprintf(stderr, "Invalid resource\n");
    }
}

int main() {
    Resource resource;
    resource.data = malloc(1024);
    resource.size = 1024;
    release_resource(&resource);
    return 0;
}