#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Resource;

void release_resource(Resource *resource) {
    if (resource != NULL && resource->data != NULL) {
        free(resource->data);
        resource->data = NULL;
        resource->size = 0;
    }
}

int main() {
    Resource resource;
    resource.size = 10;
    resource.data = (int *)malloc(resource.size * sizeof(int));
    if (resource.data != NULL) {
        for (int i = 0; i < resource.size; i++) {
            resource.data[i] = i;
        }
        release_resource(&resource);
        printf("Resource released\n");
    } else {
        printf("Memory allocation failed\n");
    }
    return 0;
}