#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
} Resource;

void use_resource(Resource *res) {
    printf("Using resource data: %d\n", res->data[0]);
}

int main() {
    Resource *res = (Resource *)malloc(sizeof(Resource));
    res->data = (int *)malloc(sizeof(int));
    res->data[0] = 42;
    free(res->data);
    use_resource(res);
    free(res);
    return 0;
}