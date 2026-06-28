#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
} Resource;

void use_resource(Resource *res) {
    printf("Data: %d\n", *res->data);
}

int main() {
    Resource res;
    res.data = (int *)malloc(sizeof(int));
    *res.data = 42;
    free(res.data);
    use_resource(&res);
    return 0;
}