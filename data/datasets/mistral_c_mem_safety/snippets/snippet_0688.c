#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Resource;

Resource *create_resource(int size) {
    Resource *res = (Resource *)malloc(sizeof(Resource));
    res->data = (int *)malloc(size * sizeof(int));
    res->size = size;
    return res;
}

void release_resource(Resource *res) {
    free(res->data);
    res->data = NULL;
    res->size = 0;
}

int main() {
    Resource *res = create_resource(5);
    for (int i = 0; i < res->size; i++) {
        res->data[i] = i + 1;
    }
    release_resource(res);
    if (res->data == NULL) {
        printf("Resource released\n");
    }
    free(res);
    return 0;
}