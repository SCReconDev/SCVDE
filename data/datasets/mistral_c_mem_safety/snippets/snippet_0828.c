#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Resource;

void use_resource(Resource *res) {
    if (res == NULL || res->data == NULL) {
        printf("Invalid resource\n");
        return;
    }
    for (int i = 0; i < res->size; i++) {
        printf("Data[%d]: %d\n", i, res->data[i]);
    }
    free(res->data);
    free(res);
}

int main() {
    Resource *res = (Resource *)malloc(sizeof(Resource));
    if (res == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    res->size = 5;
    res->data = (int *)malloc(res->size * sizeof(int));
    if (res->data == NULL) {
        printf("Memory allocation failed\n");
        free(res);
        return 1;
    }
    for (int i = 0; i < res->size; i++) {
        res->data[i] = i;
    }
    use_resource(res);
    return 0;
}