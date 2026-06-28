#include <stdio.h>
#include <stdlib.h>

void *allocate_resource() {
    void *resource = malloc(100);
    if (resource == NULL) {
        printf("Resource allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return resource;
}

void cleanup_resource(void *resource) {
    if (resource != NULL) {
        free(resource);
        resource = NULL;
    }
}

int main() {
    void *resource = allocate_resource();
    printf("Resource allocated\n");
    cleanup_resource(resource);
    return 0;
}