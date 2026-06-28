#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Resource;

void releaseResource(Resource *resource) {
    if (resource->data != NULL) {
        free(resource->data);
        resource->data = NULL;
    }
}

void useResource(Resource *resource) {
    if (resource->data == NULL) {
        printf("Resource not initialized\n");
        return;
    }
    for (int i = 0; i < resource->size; i++) {
        printf("%d ", resource->data[i]);
    }
    printf("\n");
}

int main() {
    Resource resource;
    resource.size = 5;
    resource.data = (int *)malloc(resource.size * sizeof(int));
    if (resource.data == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    for (int i = 0; i < resource.size; i++) {
        resource.data[i] = i;
    }
    useResource(&resource);
    releaseResource(&resource);
    useResource(&resource);
    return 0;
}