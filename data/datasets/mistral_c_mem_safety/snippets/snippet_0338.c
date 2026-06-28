#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
} Resource;

void release_resource(Resource *res) {
    free(res->data);
    res->data = NULL;
}

int main() {
    Resource res;
    res.data = (int *)malloc(10 * sizeof(int));
    if (res.data == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    release_resource(&res);
    res.data[0] = 10;
    printf("Value: %d\n", res.data[0]);
    return 0;
}