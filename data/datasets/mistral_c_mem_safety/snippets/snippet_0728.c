#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Resource;

Resource* create_resource(int size) {
    Resource *res = (Resource*)malloc(sizeof(Resource));
    if (res == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    res->data = (int*)malloc(size * sizeof(int));
    if (res->data == NULL) {
        printf("Memory allocation failed\n");
        free(res);
        return NULL;
    }
    res->size = size;
    return res;
}

void release_resource(Resource *res) {
    if (res != NULL) {
        if (res->data != NULL) {
            free(res->data);
        }
        free(res);
    }
}

int main() {
    Resource *res = create_resource(10);
    if (res != NULL) {
        for (int i = 0; i < res->size; i++) {
            res->data[i] = i;
        }
        for (int i = 0; i < res->size; i++) {
            printf("%d ", res->data[i]);
        }
        printf("\n");
        release_resource(res);
    }
    return 0;
}