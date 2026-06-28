#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
} Resource;

void release_resource(Resource *res) {
    free(res->data);
}

int main() {
    Resource res;
    res.data = (int *)malloc(sizeof(int));
    *res.data = 10;
    release_resource(&res);
    printf("Value: %d\n", *res.data);
    return 0;
}