#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Resource;

void release_resource(Resource *res) {
    if (res->data != NULL) {
        free(res->data);
        res->data = NULL;
    }
}

int main() {
    Resource res;
    res.size = 10;
    res.data = (int *)malloc(res.size * sizeof(int));
    if (res.data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    for (int i = 0; i < res.size; i++) {
        res.data[i] = i;
    }
    printf("Resource created\n");
    release_resource(&res);
    printf("Resource released\n");
    return 0;
}