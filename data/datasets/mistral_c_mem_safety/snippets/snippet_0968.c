#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Resource;

void release_resource(Resource *resource) {
    if (resource == NULL || resource->data == NULL) {
        printf("Null resource or data\n");
        return;
    }

    free(resource->data);
    resource->data = NULL;
    resource->size = 0;
}

int main() {
    Resource resource;
    resource.data = (int *)malloc(sizeof(int) * 10);
    resource.size = 10;

    if (resource.data == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (size_t i = 0; i < resource.size; i++) {
        resource.data[i] = i;
    }

    printf("Resource created\n");
    release_resource(&resource);
    printf("Resource released\n");
    return 0;
}