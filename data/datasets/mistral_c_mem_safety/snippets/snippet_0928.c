#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Resource;

void release_resource(Resource *resource) {
    if (resource->data != NULL) {
        free(resource->data);
        resource->data = NULL;
    }
}

int main() {
    Resource resource;
    resource.size = 10;
    resource.data = (int *)malloc(resource.size * sizeof(int));
    if (resource.data == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    for (int i = 0; i < resource.size; i++) {
        resource.data[i] = i;
    }
    release_resource(&resource);
    if (resource.data == NULL) {
        printf("Resource released successfully\n");
    }
    return 0;
}