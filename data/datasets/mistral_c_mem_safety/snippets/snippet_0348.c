#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
} Resource;

void release_resource(Resource *res) {
    free(res->data);
}

void use_resource(Resource *res) {
    printf("Using resource data: %d\n", *res->data);
}

int main() {
    Resource res;
    res.data = (int *)malloc(sizeof(int));
    *res.data = 42;
    release_resource(&res);
    use_resource(&res);
    return 0;
}