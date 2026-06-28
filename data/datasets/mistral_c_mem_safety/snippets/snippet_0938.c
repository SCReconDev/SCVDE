#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;
    size_t size;
} Resource;

void release_resource(Resource* res) {
    if (res->data != NULL) {
        free(res->data);
        res->data = NULL;
    }
}

void use_resource(Resource* res) {
    if (res->data == NULL) {
        fprintf(stderr, "Resource not allocated\n");
        return;
    }

    for (size_t i = 0; i < res->size; i++) {
        printf("Resource data %zu: %d\n", i, res->data[i]);
    }
}

int main() {
    Resource res;
    res.size = 5;
    res.data = (int*)malloc(res.size * sizeof(int));

    if (res.data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (size_t i = 0; i < res.size; i++) {
        res.data[i] = i;
    }

    use_resource(&res);

    release_resource(&res);

    use_resource(&res);

    return 0;
}