#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Resource;

Resource *create_resource(int size) {
    Resource *res = (Resource *)malloc(sizeof(Resource));
    if (res == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    res->data = (int *)malloc(size * sizeof(int));
    if (res->data == NULL) {
        printf("Memory allocation failed\n");
        free(res);
        exit(1);
    }
    res->size = size;
    return res;
}

void cleanup_resource(Resource *res) {
    free(res->data);
    free(res);
}

int main() {
    Resource *res = create_resource(5);
    for (int i = 0; i < res->size; i++) {
        res->data[i] = i + 1;
    }
    for (int i = 0; i < res->size; i++) {
        printf("%d ", res->data[i]);
    }
    cleanup_resource(res);
    return 0;
}