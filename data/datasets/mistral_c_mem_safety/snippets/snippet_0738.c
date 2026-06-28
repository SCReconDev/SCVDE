#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Resource;

Resource *create_resource(int size) {
    Resource *resource = (Resource *)malloc(sizeof(Resource));
    if (resource == NULL) {
        printf("Resource creation failed\n");
        exit(EXIT_FAILURE);
    }
    resource->data = (int *)malloc(size * sizeof(int));
    if (resource->data == NULL) {
        printf("Data allocation failed\n");
        free(resource);
        exit(EXIT_FAILURE);
    }
    resource->size = size;
    return resource;
}

void release_resource(Resource *resource) {
    if (resource != NULL) {
        if (resource->data != NULL) {
            free(resource->data);
        }
        free(resource);
    }
}

int main() {
    Resource *resource = create_resource(10);
    printf("Resource created\n");
    release_resource(resource);
    return 0;
}