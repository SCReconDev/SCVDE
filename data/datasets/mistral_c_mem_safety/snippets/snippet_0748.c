#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Resource;

void release_resource(Resource *res) {
    if (res != NULL && res->data != NULL) {
        free(res->data);
        res->data = NULL;
        res->size = 0;
    }
}

int main() {
    Resource res;
    res.size = 10;
    res.data = (int *)malloc(res.size * sizeof(int));
    if (res.data != NULL) {
        for (int i = 0; i < res.size; i++) {
            res.data[i] = i;
        }
        printf("Resource allocated and initialized\n");
    } else {
        printf("Resource allocation failed\n");
    }
    release_resource(&res);
    return 0;
}