#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;
} Resource;

void release_resource(Resource* res) {
    free(res->data);
}

int main() {
    Resource res;
    res.data = (int*)malloc(10 * sizeof(int));
    for (int i = 0; i < 10; i++) {
        res.data[i] = i;
    }
    release_resource(&res);
    printf("Value: %d\n", res.data[0]);
    return 0;
}