#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;
    int size;
} Resource;

void release_resource(Resource* resource) {
    if (resource != NULL && resource->data != NULL) {
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
        for (int i = 0; i < resource.size; i++) {
            resource.data[i] = i;
        }
        for (int i = 0; i < resource.size; i++) {
            printf("%d ", resource.data[i]);
        }
        printf("\n");
        release_resource(&resource);
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}