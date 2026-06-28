#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Resource;

void releaseResource(Resource *resource) {
    if (resource == NULL || resource->data == NULL) {
        printf("Null resource or data.\n");
        return;
    }

    free(resource->data);
    resource->data = NULL;
    resource->size = 0;
}

void useResource(Resource *resource) {
    if (resource == NULL || resource->data == NULL) {
        printf("Null resource or data.\n");
        return;
    }

    for (size_t i = 0; i < resource->size; i++) {
        printf("%d ", resource->data[i]);
    }
    printf("\n");
}

int main() {
    Resource resource;
    resource.size = 5;
    resource.data = (int *)malloc(resource.size * sizeof(int));

    if (resource.data == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (size_t i = 0; i < resource.size; i++) {
        resource.data[i] = i;
    }

    useResource(&resource);
    releaseResource(&resource);

    useResource(&resource);

    return 0;
}