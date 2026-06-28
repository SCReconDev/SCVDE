#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
} Resource;

void release_resource(Resource* resource) {
    if (resource != NULL) {
        free(resource);
    }
}

int main() {
    Resource* resource = (Resource*)malloc(sizeof(Resource));
    if (resource != NULL) {
        resource->value = 42;
        printf("Resource value: %d\n", resource->value);
        release_resource(resource);
    }
    return 0;
}