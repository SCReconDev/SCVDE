#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
} Resource;

void use_resource(Resource *res) {
    printf("Using resource: %d\n", *res->data);
}

int main() {
    Resource *res = (Resource *)malloc(sizeof(Resource));
    res->data = (int *)malloc(sizeof(int));
    *res->data = 42;
    free(res->data);
    use_resource(res);
    free(res);
    return 0;
}