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
    }
}

int main() {
    Resource resource;
    resource.size = 5;
    resource.data = (int *)malloc(resource.size * sizeof(int));

    if (resource.data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < resource.size; i++) {
        resource.data[i] = i * 2;
    }

    printf("Resource data:\n");
    for (size_t i = 0; i < resource.size; i++) {
        printf("Data[%zu]: %d\n", i, resource.data[i]);
    }

    release_resource(&resource);
    return 0;
}