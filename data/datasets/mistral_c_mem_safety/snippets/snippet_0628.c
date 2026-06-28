#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Resource;

void release_resource(Resource *res) {
    if (res == NULL || res->data == NULL) {
        printf("Invalid resource\n");
        return;
    }
    free(res->data);
    res->data = NULL;
    res->size = 0;
    printf("Resource released\n");
}

int main() {
    Resource res;
    res.size = 10;
    res.data = (int *)malloc(res.size * sizeof(int));
    if (res.data == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    for (int i = 0; i < res.size; i++) {
        res.data[i] = i;
    }
    release_resource(&res);
    return 0;
}