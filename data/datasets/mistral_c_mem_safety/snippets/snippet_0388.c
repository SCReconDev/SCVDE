#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
} Resource;

void release_resource(Resource *res) {
    free(res->data);
    res->data = NULL;
}

void use_resource(Resource *res) {
    if (res->data != NULL) {
        printf("Using resource\n");
    }
}

int main() {
    Resource res;
    res.data = (int *)malloc(10 * sizeof(int));
    release_resource(&res);
    use_resource(&res);
    return 0;
}