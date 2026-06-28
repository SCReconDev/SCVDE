#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Resource;

void release_resource(Resource *res) {
    if (res->data != NULL) {
        free(res->data);
        res->data = NULL;
        res->size = 0;
    }
}

int main() {
    Resource res;
    res.size = 10;
    res.data = (int *)malloc(res.size * sizeof(int));
    if (res.data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < res.size; i++) {
        res.data[i] = i;
    }

    printf("Resource data:\n");
    for (size_t i = 0; i < res.size; i++) {
        printf("%d ", res.data[i]);
    }
    printf("\n");

    release_resource(&res);
    return 0;
}