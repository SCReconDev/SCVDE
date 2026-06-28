#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;
    size_t size;
} Resource;

Resource* create_resource(size_t size) {
    Resource* res = (Resource*)malloc(sizeof(Resource));
    if (res == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    res->data = (int*)malloc(size * sizeof(int));
    if (res->data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(res);
        exit(EXIT_FAILURE);
    }

    res->size = size;

    return res;
}

void release_resource(Resource* res) {
    if (res != NULL) {
        free(res->data);
        free(res);
    }
}

int main() {
    Resource* res = create_resource(10);

    for (size_t i = 0; i < res->size; i++) {
        res->data[i] = i;
    }

    for (size_t i = 0; i < res->size; i++) {
        printf("%d ", res->data[i]);
    }
    printf("\n");

    release_resource(res);

    return 0;
}