#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Resource;

void release_resource(Resource *resource) {
    if (resource != NULL && resource->data != NULL) {
        free(resource->data);
        resource->data = NULL;
        resource->size = 0;
    }
}

void use_resource(Resource *resource) {
    if (resource == NULL || resource->data == NULL) {
        fprintf(stderr, "Invalid resource\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < resource->size; i++) {
        printf("%d ", resource->data[i]);
    }
    printf("\n");
}

int main() {
    Resource resource;
    resource.size = 10;
    resource.data = (int *)malloc(resource.size * sizeof(int));

    if (resource.data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < resource.size; i++) {
        resource.data[i] = i;
    }

    use_resource(&resource);

    release_resource(&resource);

    return 0;
}