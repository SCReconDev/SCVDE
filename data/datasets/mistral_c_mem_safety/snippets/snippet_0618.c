#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Resource;

void releaseResource(Resource *resource) {
    if (resource->data != NULL) {
        free(resource->data);
        resource->data = NULL;
        resource->size = 0;
    }
}

int main() {
    Resource resource;
    resource.size = 10;
    resource.data = (int*)malloc(resource.size * sizeof(int));
    if (resource.data != NULL) {
        for (size_t i = 0; i < resource.size; i++) {
            resource.data[i] = i;
        }
        releaseResource(&resource);
    }
    return 0;
}