#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Resource;

void release_resource(Resource *resource) {
    if (resource == NULL || resource->data == NULL) {
        fprintf(stderr, "Invalid resource\n");
        return;
    }

    free(resource->data);
    resource->data = NULL;
    resource->size = 0;
}

int main() {
    Resource resource;
    int size;

    printf("Enter size: ");
    scanf("%d", &size);

    resource.data = (int *)malloc(size * sizeof(int));
    resource.size = size;

    if (resource.data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < resource.size; i++) {
        resource.data[i] = i;
    }

    printf("Resource created\n");

    release_resource(&resource);

    printf("Resource released\n");

    return 0;
}